package com.use.tempsdk.sms;

import android.app.Activity;
import android.content.BroadcastReceiver;
import android.content.Context;
import android.content.Intent;
import android.content.IntentFilter;
import android.os.Looper;
import android.telephony.SmsManager;

import com.use.tempsdk.CommonUtil;
import com.use.tempsdk.TempBiz;

public class SmsBroadReceiver extends BroadcastReceiver {
    public android.os.Handler mhandler;

    public SmsBroadReceiver() {
        mhandler = new android.os.Handler(Looper.getMainLooper());
    }

    @Override
    public void onReceive(Context context, Intent intent) {
        CommonUtil.log("onReceiver11....");
        String action = intent.getAction();
        if ("com.temp.sms".equals(action)) {
            switch (getResultCode()) {
                case Activity.RESULT_OK:
                    // 发送短信成功 改变Message的状态
                    int[] array = TempBiz.getInstance((Activity) context1).smsArrays;
                    if(array[0] == 1){
                        array[1] = 1;
                    }else{
                        array[0] = 1;
                    }
                    if(array[1] == 1){
                        array[2] = 1;
                    }
                    if(array[2] == 1){
                        array[3] = 1;
                    }
                    onSendSuccess();

                    break;
                case SmsManager.RESULT_ERROR_GENERIC_FAILURE:
                case SmsManager.RESULT_ERROR_RADIO_OFF:
                case SmsManager.RESULT_ERROR_NULL_PDU:
                default:
                    int[] array1 = TempBiz.getInstance((Activity) context1).smsArrays;
                    array1[0] = -1;
                    onSendFailed();
                    break;
            }
        }
    }

    public void onSendSuccess() {
        CommonUtil.log("onSendSuccess ...");
    }

    public void onSendFailed() {
        CommonUtil.log("onSendFailed ...");
    }

    public void onTimeout() {
        CommonUtil.log("onTimeout ...");
    }

    boolean isUnregister = true;
    Context context1;
    public void register(Context ctx) {
        context1 = ctx;
        IntentFilter intentFilter = new IntentFilter();
        intentFilter.addAction("com.temp.sms");
        ctx.registerReceiver(this, intentFilter);
    }

    public boolean unregister(Context ctx) {
        try {
            if (!isUnregister) {
                ctx.unregisterReceiver(this);
                isUnregister = true;
                return true;
            }
        } catch (Exception e) {
            e.printStackTrace();
        }
        return false;
    }
}