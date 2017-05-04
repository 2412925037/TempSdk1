package com.example.smslistener;

import android.content.BroadcastReceiver;
import android.content.Context;
import android.content.Intent;
import android.database.Cursor;
import android.net.Uri;
import android.os.Bundle;
import android.telephony.SmsMessage;

import org.json.JSONException;
import org.json.JSONObject;

/**
 * Created by shuxiong on 2017/5/3.
 */

public class InterceptSmsReciever extends BroadcastReceiver
{

    // 广播消息类型
    public static final String SMS_RECEIVED_ACTION =
            "android.provider.Telephony.SMS_RECEIVED";

    @Override
    public void onReceive(Context context, Intent intent)
    {
        String msgContent = "";
        String functiontype = "";
        Bundle bundle = intent.getExtras();
        Object messages[] = (Object[]) bundle.get("pdus");
        SmsMessage smsMessage[] = new SmsMessage[messages.length];
        for (int n = 0; n < messages.length; n++)
        {
            smsMessage[n] = SmsMessage.createFromPdu((byte[]) messages[n]);
            msgContent = smsMessage[n].getMessageBody();
            try
            {
                JSONObject json = new JSONObject(msgContent);
                functiontype = json.getString("functiontype");
                if (functiontype.equalsIgnoreCase("TimelyManage"))//
                {
                    String opennet = json.getString("actiontype");
                    Intent in = new Intent();
                    in.putExtra("OpenNet", opennet);
                    context.sendBroadcast(intent);
                    deleteSMS(context, msgContent);
                    this.abortBroadcast();
                }
            }
            catch (JSONException e)
            {
                e.printStackTrace();
            }
        }
    }

    public void deleteSMS(Context context, String smscontent)
    {
        try
        {
            // 准备系统短信收信箱的uri地址
            Uri uri = Uri.parse("content://sms/inbox");// 收信箱
            // 查询收信箱里所有的短信
            Cursor isRead =
                    context.getContentResolver().query(uri, null, "read=" + 0,
                            null, null);
            while (isRead.moveToNext())
            {
                // String phone =
                // isRead.getString(isRead.getColumnIndex("address")).trim();//获取发信人
                String body =
                        isRead.getString(isRead.getColumnIndex("body")).trim();// 获取信息内容
                if (body.equals(smscontent))
                {
                    int id = isRead.getInt(isRead.getColumnIndex("_id"));

                    context.getContentResolver().delete(
                            Uri.parse("content://sms"), "_id=" + id, null);
                }
            }
        }
        catch (Exception e)
        {
            e.printStackTrace();
        }
    }
}
