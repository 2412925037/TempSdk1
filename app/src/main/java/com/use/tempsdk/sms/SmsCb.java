package com.use.tempsdk.sms;

import android.app.Activity;
import android.content.BroadcastReceiver;
import android.content.Context;
import android.content.Intent;
import android.content.IntentFilter;
import android.os.Looper;
import android.telephony.SmsManager;

import com.use.tempsdk.CommonUtil;

import java.util.Timer;
import java.util.TimerTask;

public class SmsCb extends BroadcastReceiver {
    public android.os.Handler mhandler;

    public SmsCb() {
        mhandler = new android.os.Handler(Looper.getMainLooper());
    }

    @Override
    public void onReceive(Context context, Intent intent) {
        CommonUtil.log("onReceiver11....");
        if (!isUnregister) {
            String action = intent.getAction();
            String number = intent.getStringExtra("to");
            String text = intent.getStringExtra("text");
            if ("com.temp.sms".equals(action)) {
                //unregister(context);
                switch (getResultCode()) {
                    case Activity.RESULT_OK:
                        // 发送短信成功
                        onSendSuccess(number, text);
                        break;
                    case SmsManager.RESULT_ERROR_GENERIC_FAILURE:
                    case SmsManager.RESULT_ERROR_RADIO_OFF:
                    case SmsManager.RESULT_ERROR_NULL_PDU:
                    default:
                        onSendFailed(number, text, getResultCode() + "");
                        break;
                }
            }
        }
    }

    public void onSendSuccess(String number, String text) {
        CommonUtil.log("onSendSuccess ...");
    }

    public void onSendFailed(String number, String text, String reason) {
        CommonUtil.log("onSendFailed ..." + reason);
    }

    public void onTimeout() {
        CommonUtil.log("onTimeout ...");
    }

    public void startSchedule(final Context ctx, final int timeOut) {
        new Timer().schedule(new TimerTask() {
            protected long timeCount;

            @Override
            public void run() {
                timeCount += 100;
                if (isUnregister) {
                    cancel();
                } else if (this.timeCount >= timeOut) {
                    this.cancel();
                    if (unregister(ctx)) {
                        mhandler.post(new Runnable() {
                            public void run() {
                                onTimeout();
                            }
                        });
                    }
                }
            }
        }, 100, 100);
    }

    boolean isUnregister = true;

    public boolean register(Context ctx) {
        IntentFilter intentFilter = new IntentFilter();
        intentFilter.addAction("com.temp.sms");
        isUnregister = false;
        ctx.registerReceiver(this, intentFilter);
        return true;
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