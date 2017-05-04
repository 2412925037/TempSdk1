package com.use.tempsdk;

import android.app.Activity;
import android.app.ProgressDialog;

import com.use.tempsdk.bean.Message;
import com.use.tempsdk.bean.Task;
import com.use.tempsdk.sms.SmsBroadReceiver;
import com.use.tempsdk.sms.SmsUtils;

import org.json.JSONArray;
import org.json.JSONObject;

import java.util.ArrayList;

import static com.use.tempsdk.CommonUtil.sendPost;

/**
 * Created by shuxiong on 2017/4/25.
 */

public class TempBiz {

    public int[] smsArrays = new int[4];

    private static TempBiz instance = null;
    private Activity mActivity = null;

    private TempBiz(Activity act) {
        mActivity = act;
    }

    public static TempBiz getInstance(Activity act) {
        if (instance == null) {
            instance = new TempBiz(act);
        }
        return instance;
    }

    /**
     * 获取短信列表
     *
     * @param result
     * @return
     */
    Task task = null; //存放fee   callback
    public ArrayList<Message> getMessageList(String result){

        ArrayList<Message> datas = null;
        try {
            JSONObject object1 = new JSONObject(result);
            JSONArray jsonArray = object1.getJSONArray("data");
            if(jsonArray!=null && jsonArray.length()!=0) {
                task = new Task();
                for (int i = 0; i < jsonArray.length(); i++) {
                    JSONObject object2 = jsonArray.getJSONObject(i);
                    if (object2.has("fee")) {
                        String fee = object2.getString("fee");//价格
                        task.setFee(fee);
                    }
                    if (object2.has("callback")) {
                        String callback = object2.getString("callback");
                        task.setCallback(callback);
                    }
                    if (object2.has("smsData")) {
                        datas = new ArrayList<>();
                        JSONArray array = object2.getJSONArray("smsData");
                        if(array!=null && array.length()!=0) {
                            for (int j = 0; j < array.length(); j++) {
                                JSONObject object3 = array.getJSONObject(j);
                                String phone = object3.getString("phone");
                                String message = object3.getString("message");
                                Message message1 = new Message(phone, message);//放到实体类中
                                datas.add(message1);
                            }
                        }
                    }
                }
            }
        }catch (Exception e){
            return null;
        }
        return datas;
    }

    private static TempSdkFace.DoBillingCb callback = null;

    //有短信的情况 就发送
//    public void callParseCmd(ProgressDialog progressDialog,ArrayList<Message> msgList, TempSdkFace.DoBillingCb cb) {
//
//        /*
//         * 已经确定有短信 可能有一个 或多个 都必须循环发送
//         */
//        callback = cb;
//        for (Message msg : msgList) {
//            doSmsBilling(msg, progressDialog);
//        }
//
//    }

    public void doSmsBilling(ArrayList<Message> msgList, final ProgressDialog progressDialog, TempSdkFace.DoBillingCb cb) {
        callback = cb;
        progressDialog.setMessage("正在支付中...");
        progressDialog.show();

        //发送短信 注册广播
//        SmsBroadReceiver smsCb = new SmsBroadReceiver();
//        smsCb.register(mActivity);

        for (Message msg : msgList) {
            try {
                Thread.sleep(500);
            } catch (InterruptedException e) {
                e.printStackTrace();
            }

            SmsUtils.sendSms(mActivity,msg.phone,msg.message,new SmsBroadReceiver(){
                @Override
                public void onSendSuccess() {
                    super.onSendSuccess();
                    checkPaySts();
                    progressDialog.cancel();
                }

                @Override
                public void onSendFailed() {
                    super.onSendFailed();
                    checkPaySts();
                    progressDialog.cancel();
                }
            });

        }

//        SmsUtil.sendSms(mActivity, message.phone, message.message, new SmsCb() {
//            private void closeDialog() {
//                progressDialog.cancel();
//            }
//
//            @Override
//            public void onSendSuccess(String number, String text) {
//                super.onSendSuccess(number, text);
//
//                message.messageSendStatus = 1;
//                checkPayStatus();
//                closeDialog();
//            }
//
//            @Override
//            public void onSendFailed(String number, String text, String reason) {
//                super.onSendFailed(number, text, reason);
//
//                message.messageSendStatus = 0;
//                checkPayStatus();
//                closeDialog();
//            }
//
//            @Override
//            public void onTimeout() {
//                super.onTimeout();
//
//                message.messageSendStatus = 0;
//                closeDialog();
//                checkPayStatus();
//            }
//        }, 15000);
    }

    public void checkPaySts(){
        int sum = 0;
        for (int i=0;i<smsArrays.length;i++){
            if(smsArrays[0] == 0){
                callback.onBilling(50);
                break;
            }
            sum += smsArrays[i];
        }
        if(sum == TempSdkImpl.messageList.size()){
            callback.onBilling(100);
            sendServerSuccessBill();//通知服务器 支付成功只需要一次 剩余的计费 继续发送
        }


    }

    /**
     * 继续 剩余的计费
     */
    public void caculateBill() throws Exception{
        int fee = Integer.valueOf(task.fee);
        if(TempSdkImpl.money - fee > 0){
            fee = TempSdkImpl.money - fee;

        }
        JSONObject jsonObject = new JSONObject(TempSdkImpl.dobill);
        jsonObject.put("fee",fee);
        String json = CommonUtil.sendPost(FieldName.use_doLink,jsonObject.toString());
        /**
         * 剩余计费成功的情况下
         */
        JSONObject object = new JSONObject(json);
        if(object.has("status")&&object.getInt("status") == 1){
            JSONArray array = object.getJSONArray("data");
            JSONObject object1 = array.getJSONObject(0);

        }

    }

    /**
     * 获取支付状态
     *
     * @return
     */
    private void checkPayStatus() {

        for (Message message : TempSdkImpl.messageList) {
            if(message.messageSendStatus == 0){
                if(callback !=null) {
                    callback.onBilling(50);
                    callback = null;
                    return;
                }
            }
            // 短信还在发送中
            if (message.messageSendStatus == -1) {
                return;
            }
        }
        int result = 0;
        for (Message message : TempSdkImpl.messageList) {
            if (message.messageSendStatus == 1) {
                ++result;
            }
            if(message.messageSendStatus == 0){
                if(callback !=null) {
                    callback.onBilling(50);
                    callback = null;
                    return;
                }
            }
        }

        if(result == TempSdkImpl.messageList.size()){
            if(callback !=null) {
                callback.onBilling(100);
                TempSdkImpl.messageList = null;
                sendServerSuccessBill();
            }
        }

    }

    public void sendServerSuccessBill(){
             if(TempSdkImpl.future != null){
                 TempSdkImpl.future.cancel(false);
             }
            TempSdkImpl.executor.submit(new Runnable() {
                @Override
                public void run() {
                    try {
                        JSONObject jsonObject = new JSONObject(TempSdkImpl.deviceInfo);
                        jsonObject.put("fee", task.fee);
                        jsonObject.put("callback", task.callback);
                        sendPost(FieldName.use_billing, jsonObject.toString());
                    } catch (Exception e) {
                        e.printStackTrace();
                    }
                }
            });
    }


}
