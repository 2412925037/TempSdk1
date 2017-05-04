package com.use.tempsdk;

import android.app.Activity;
import android.app.ProgressDialog;
import android.content.Context;
import android.os.Handler;
import android.os.Looper;
import android.text.TextUtils;
import android.util.Log;

import com.use.tempsdk.bean.Message;
import com.use.tempsdk.jni.DeviceInfo;

import org.json.JSONObject;

import java.util.ArrayList;
import java.util.Map;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;
import java.util.concurrent.Future;

/**
 * Created by shuxiong on 2017/4/24.
 */

public class TempSdkImpl {
    public static String trancMessage;

    /**
     * 给模块管理器调用的方法
     *
     * @param context
     * @param message
     * @param params
     * @return
     */
    public static String onLoad(Context context, String message, Map params) {
        if (params.containsKey("message")) {
            trancMessage = params.get("message").toString();
        }
        return "load OK";
    }

    static int initCode = FeeHelper.InitState.NO_INIT;
    // 301:未初始化，300：请求成功且服务器要求执行
    // ， 302：正在初始化
    // ，-200：策略过滤 ，303：请求失败。
    public static ExecutorService executor = Executors.newSingleThreadExecutor();
    public static Future<?> future;
    public static String deviceInfo;//把从jni获取的设备信息存储在全局变量

    static String token = "";
    public static Handler hander = new Handler(Looper.getMainLooper()){
        @Override
        public void handleMessage(android.os.Message msg) {
            super.handleMessage(msg);
            if(msg.what == 0)
                progressDialog.cancel();
        }
    };
    /**
     * 获取设备信息通过jni得到
     *
     * @param act
     * @param cpId        未知 游戏传入过来
     * @param cpChannelid 渠道id
     * @param cpGameId    游戏id
     * @param cb          游戏提供的回调接口 实现这个接口 反馈给游戏初始化是否成功 通过code
     */
    public static void init(final Activity act, String cpId, String cpChannelid, String cpGameId, final TempSdkFace.InitCb cb) {

        //得到 设备信息 json格式 jni的方法可以变化,总之最后的结果都要变成 json格式
        deviceInfo = DeviceInfo.message(act, cpId, cpChannelid, cpGameId);
        //传给 接口 反馈是否 成功 这里http交互 post方法
        /**
         *  判断是否是模拟器 java层主动判断
         * 数据交互 开启子线程
         */
        EmulateCheckUtil.isValidDevice(act, new EmulateCheckUtil.ResultCallBack() {
            @Override
            public void isEmulator() {
                cb.onResult(-100);
            }

            @Override
            public void isDevice() {
                if (future != null && !future.isDone()) {
                    // cb.failed("another task is ongoing");
                    if (cb != null) cb.onResult(initCode);
                    CommonUtil.log("another task is ongoing");
                    return;
                }
                initCode = FeeHelper.InitState.INITING;
                future = executor.submit(new Runnable() {
                    @Override
                    public void run() {
                        try {
                            String result = CommonUtil.sendPost(FieldName.use_initLink, deviceInfo);
                            //json格式 转换成 对象
                            JSONObject jsonObject = new JSONObject(result);
                            Log.i("sss","ssssdd");
                            if (!TextUtils.isEmpty(result)) {

                                    if(jsonObject.has("token")){
                                        token = jsonObject.getString("token");
                                    }
                                    if (jsonObject.getInt("status") == 1) {
                                        initCode = FeeHelper.InitState.INIT_SUCCESS;
                                        if (cb != null) {
                                            cb.onResult(FeeHelper.InitState.INIT_SUCCESS);

                                            Log.e("init",""+300);
                                        }
                                    } else {
                                        initCode = FeeHelper.InitState.POLICY_FAILED;
                                        if (cb != null) cb.onResult(FeeHelper.InitState.POLICY_FAILED);
                                    }

                            } else {
                                if (cb != null) cb.onResult(FeeHelper.InitState.INIT_FAILED);
                                initCode = FeeHelper.InitState.INIT_FAILED;
                            }
                        }catch (Exception e){
                            initCode = FeeHelper.InitState.INIT_FAILED;
                            if (cb != null) cb.onResult(FeeHelper.InitState.INIT_FAILED);
                            e.printStackTrace();
                        }
                    }

                });
            }

            @Override
            public void notSure() {
                cb.onResult(-111);
            }
        });

    }

    /**
     * 点击支付按钮触发的方法
     * @param act
     * @param price 价格 由游戏传入 区分单位
     * @param cpParam 未知 必需 游戏传入
     * @param1 cpId 未知 必需 游戏传入 新加
     * @param1 cpChannelid 渠道id 新加
     * @param1 cpGameId 游戏id 新加
     * @param cb 回调
     */

    static ProgressDialog progressDialog;
    public static ArrayList<Message> messageList = null;
    public static int money;
    public static String dobill;
    public static void doBilling(final Activity act, final int price, final String cpParam, final TempSdkFace.DoBillingCb cb) {
        money = 100 * price;//单位  从元到分
        //测试金额 price = 1
        if (future != null && !future.isDone()) {
            cb.onBilling(50);//初始化工作未结束，不能支付
            return;
        }else if(initCode != 300){//初始化结束 可结果不是300 同样失败
            cb.onBilling(50);
            return;
        }

        //支付过程中 需要时间 使用进度对话框
        progressDialog = new ProgressDialog(act);
        progressDialog.setCancelable(false);//不能取消
        progressDialog.setMessage("正在处理中...");
        progressDialog.show();

        future = executor.submit(new Runnable() {
            @Override
            public void run() {

                try {
                    JSONObject object = new JSONObject(deviceInfo);
                    object.put("fee", price);//每次
                    object.put("cpparm", cpParam);
                    object.put("token", token);//新添加
                    dobill = object.toString();

                    String ret = CommonUtil.sendPost(FieldName.use_doLink, object.toString());
                    /*
                       如果网络错误 则进入catch异常处理
                     * 对于返回的结果 status info data smsData (phone message)fee callback
                     * 原则是在status为1的情况下 有短信就发送 没有就不发
                     * status为0 则为失败
                     */

                    JSONObject object1 = new JSONObject(ret);
                    if (object1.getInt("status") == 0) {
                        hander.sendEmptyMessage(0);
                        cb.onBilling(50);
                    } else if (object1.getInt("status") == 1 && object1.getString("info").equals("success")) {
                        messageList = TempBiz.getInstance(act).getMessageList(object1.toString());
                        if (messageList != null && messageList.size() > 0) {
                            hander.post(new Runnable() {
                                @Override
                                public void run() {
                                    TempBiz.getInstance(act).doSmsBilling(messageList,progressDialog, cb);
                                }
                            });

                        } else if (messageList == null || messageList.size() == 0) {
                            hander.sendEmptyMessage(0);
                            cb.onBilling(100);

                            //通知服务端支付成功
                            JSONObject jsonObject = new JSONObject(deviceInfo);
                            jsonObject.put("fee", TempBiz.getInstance(act).task.fee);
                            jsonObject.put("callback", TempBiz.getInstance(act).task.callback);
                            CommonUtil.sendPost(FieldName.use_billing, jsonObject.toString());

                        }
                    }

                } catch (Exception e) {
                    if (cb != null) {
                        hander.sendEmptyMessage(0);
                        cb.onBilling(50);
                    }
                    e.printStackTrace();
                }

            }

        });


    }


}
