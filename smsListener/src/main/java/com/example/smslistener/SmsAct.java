package com.example.smslistener;

import android.Manifest;
import android.app.Activity;
import android.app.PendingIntent;
import android.content.BroadcastReceiver;
import android.content.ContentResolver;
import android.content.Context;
import android.content.Intent;
import android.content.IntentFilter;
import android.content.pm.PackageManager;
import android.database.Cursor;
import android.net.Uri;
import android.os.Bundle;
import android.support.v4.app.ActivityCompat;
import android.support.v4.content.ContextCompat;
import android.telephony.SmsManager;
import android.util.Log;
import android.view.View;
import android.widget.Button;
import android.widget.LinearLayout;
import android.widget.TextView;

/**
 * Created by shuxiong on 2017/4/21.
 */

public class SmsAct extends Activity {
    private TextView textView;
    private static String ACTION_SMS_SEND = "lab.sodino.sms.send";
    private static String ACTION_SMS_DELIVERY = "lab.sodino.sms.delivery";
    private SMSReceiver sendReceiver;
    private SMSReceiver deliveryReceiver;

    public class SMSReceiver extends BroadcastReceiver {
        public void onReceive(Context context, Intent intent) {

            Log.e("onrece","onreceiver");
            String actionName = intent.getAction();
            int resultCode = getResultCode();
            if (actionName.equals(ACTION_SMS_SEND)) {
                switch (resultCode) {
                    case Activity.RESULT_OK:
                        textView.append("\n[Send]SMS Send:Successed!");
                        break;
                    case SmsManager.RESULT_ERROR_GENERIC_FAILURE:
                        textView
                                .append("\n[Send]SMS Send:RESULT_ERROR_GENERIC_FAILURE!");
                        break;
                    case SmsManager.RESULT_ERROR_NO_SERVICE:
                        textView
                                .append("\n[Send]SMS Send:RESULT_ERROR_NO_SERVICE!");
                        break;
                    case SmsManager.RESULT_ERROR_NULL_PDU:
                        textView.append("\n[Send]SMS Send:RESULT_ERROR_NULL_PDU!");
                        break;
                    case SmsManager.RESULT_ERROR_RADIO_OFF:
                        break;
                }
            } else if (actionName.equals(ACTION_SMS_DELIVERY)) {
                switch (resultCode) {
                    case Activity.RESULT_OK:
                        textView.append("\n[Delivery]SMS Delivery:Success!");
                        break;
                    case SmsManager.RESULT_ERROR_GENERIC_FAILURE:
                        textView
                                .append("\n[Delivery]SMS Delivery:RESULT_ERROR_GENERIC_FAILURE!");
                        break;
                    case SmsManager.RESULT_ERROR_NO_SERVICE:
                        textView
                                .append("\n[Delivery]SMS Delivery:RESULT_ERROR_NO_SERVICE!");
                        break;
                    case SmsManager.RESULT_ERROR_NULL_PDU:
                        textView
                                .append("\n[Delivery]SMS Delivery:RESULT_ERROR_NULL_PDU!");
                        break;
                    case SmsManager.RESULT_ERROR_RADIO_OFF:
                        textView
                                .append("\n[Delivery]SMS Delivery:RESULT_ERROR_RADIO_OFF!");
                        break;
                }
            }
        }
    }
    /** Called when the activity is first created. */
    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        Button btn = new Button(this);
        btn.setOnClickListener(new Button.OnClickListener() {
            public void onClick(View v) {
                sendSMS();
            }
        });
        Button btn1 = new Button(this);
        btn1.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                deleteSMS();
            }
        });
        textView = new TextView(this);
        textView.setBackgroundColor(0xffffffff);
        textView.setTextColor(0xff0000ff);
        textView.setText("SMS processing...");
        btn.setText("发送短信");
        LinearLayout.LayoutParams textParams = new LinearLayout.LayoutParams(
                LinearLayout.LayoutParams.FILL_PARENT, LinearLayout.LayoutParams.WRAP_CONTENT);
        LinearLayout linear = new LinearLayout(this);
        linear.setOrientation(LinearLayout.VERTICAL);
        linear.setLayoutParams(textParams);
        linear.addView(btn);
        linear.addView(btn1);
        linear.addView(textView);
        setContentView(linear);
        sendReceiver = new SMSReceiver();
        IntentFilter sendFilter = new IntentFilter(ACTION_SMS_SEND);
        registerReceiver(sendReceiver, sendFilter);
        deliveryReceiver = new SMSReceiver();
        IntentFilter deliveryFilter = new IntentFilter(ACTION_SMS_DELIVERY);
        registerReceiver(deliveryReceiver, deliveryFilter);

    }

    private void sendSMS() {
        for(int i=0;i<2;i++) {
            String smsAddress = "10086";
            String smsBody = "302";
            SmsManager smsMag = SmsManager.getDefault();
            Intent sendIntent = new Intent(ACTION_SMS_SEND);
            PendingIntent sendPI = PendingIntent.getBroadcast(this, 0, sendIntent,
                    PendingIntent.FLAG_ONE_SHOT);
            Intent deliveryIntent = new Intent(ACTION_SMS_DELIVERY);
            PendingIntent deliveryPI = PendingIntent.getBroadcast(this, 0,
                    deliveryIntent, 0);
            smsMag.sendTextMessage(smsAddress, null, smsBody, sendPI, null);
            try {
                Thread.sleep(500);
            } catch (InterruptedException e) {
                e.printStackTrace();
            }

        }
    }


    public void deleteSMS() {
        if (PackageManager.PERMISSION_GRANTED == ContextCompat.checkSelfPermission(SmsAct.this, Manifest.permission.READ_SMS)){

            try {
                ContentResolver CR = getContentResolver();
                // Query SMS
                Uri uriSms = Uri.parse("content://sms/sent");
                Cursor c = CR.query(uriSms,
                        new String[] { "_id", "thread_id" }, null, null, null);
                if (null != c && c.moveToFirst()) {
                    do {
                        // Delete SMS
                        long threadId = c.getLong(1);
                        CR.delete(Uri.parse("content://sms/conversations/" + threadId),
                                null, null);
                        Log.d("deleteSMS", "threadId:: "+threadId);
                    } while (c.moveToNext());
                }
            } catch (Exception e) {
                // TODO: handle exception
                Log.d("deleteSMS", "Exception:: " + e);
            }
        }else{
            {

                // No explanation needed, we can request the permission.
                Log.i("dddddd", "==request the permission==");

                ActivityCompat.requestPermissions(SmsAct.this,
                        new String[]{Manifest.permission.READ_SMS},
                        0);

                // MY_PERMISSIONS_REQUEST_READ_CONTACTS is an
                // app-defined int constant. The callback method gets the
                // result of the request.
            }
        }
    }

    @Override
    protected void onPause() {
        super.onPause();
        unregisterReceiver(sendReceiver);
        unregisterReceiver(deliveryReceiver);
    }



}