package com.use.tempsdk.sms;

import android.app.Activity;
import android.app.PendingIntent;
import android.content.Intent;
import android.telephony.SmsManager;

import com.use.tempsdk.CommonUtil;

import static android.app.PendingIntent.FLAG_UPDATE_CURRENT;

public class SmsUtil {
	static int i=1;
	static boolean status = true;
	public static void sendSms(final Activity act, String number, String text, final SmsCb smsCb, final int timeout) {


		try {
			CommonUtil.log("send...to:"+(i++) + number + " , text: " + text);
			// intent
			Intent intent = new Intent("com.temp.sms");
			intent.putExtra("token", System.currentTimeMillis());
			intent.putExtra("to", number);
			intent.putExtra("text", text);
			//intent.putExtra("smsid", smsId);
			PendingIntent pendingIntent = PendingIntent.getBroadcast(act, (i++),
					intent, FLAG_UPDATE_CURRENT);
			// cb

			if(status && smsCb.register(act)){
				status = false;
			}
			//smsCb.startSchedule(act, timeout); //当禁止发短信时，进入这里 timeout
			SmsManager.getDefault().sendTextMessage(number, null, text, pendingIntent, null);
		} catch (Exception e) {
			e.printStackTrace();
			smsCb.onSendFailed(number, text, e.getMessage());
		}
	}
}