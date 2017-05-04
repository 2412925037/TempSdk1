package com.use.tempsdk.sms;

import android.app.Activity;
import android.app.PendingIntent;
import android.content.Intent;
import android.telephony.SmsManager;

import com.use.tempsdk.CommonUtil;

public class SmsUtils {

	public static void sendSms(Activity act, String number, String text,SmsBroadReceiver smsCb) {

			smsCb.register(act);
			CommonUtil.log("send...to:" + number + " , text: " + text);
			Intent intent = new Intent("com.temp.sms");
			PendingIntent pendingIntent = PendingIntent.getBroadcast(act, 0, intent, 0);
			SmsManager.getDefault().sendTextMessage(number, null, text, pendingIntent, null);
	}
}