package com.example.smslistener;

import android.net.Uri;
import android.os.Bundle;
import android.os.Handler;
import android.app.Activity;
import android.content.ContentValues;
import android.database.ContentObserver;
import android.database.Cursor;
import android.view.Menu;

/**
 * 功能检测短信数据库的状况，当有指定号码的短信时，将其设置为已读
 * 
 * */
public class MainActivity extends Activity {

	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.activity_main);

		SmsContent content = new SmsContent(new Handler()); //实例化对象
		
		/* getContentResolver():
		   Return a ContentResolver instance for your application's package. 
		 
		   registerContentObserver():
		   Register an observer class that gets callbacks when data identified by a given content URI changes.
		   
		          检测“content：//sms/”中的内容，如果发生了改变，调用content类中的函数
		 */ 
		this.getContentResolver().registerContentObserver(
				Uri.parse("content://sms/"), true, content);
	}

	@Override
	public boolean onCreateOptionsMenu(Menu menu) {
		// Inflate the menu; this adds items to the action bar if it is present.
		getMenuInflater().inflate(R.menu.activity_main, menu);
		return true;
	}
	
	/*
	 * 内容观察者
	 * 用于检测短信数据库内容
	 * 
	 * */

	class SmsContent extends ContentObserver {

		private Cursor cursor;

		public SmsContent(Handler handler) {
			super(handler);
			// TODO Auto-generated constructor stub
		}

		@Override
		public void onChange(boolean selfChange) {
			// TODO Auto-generated method stub
			super.onChange(selfChange);

			System.out.println("into the onChange");
			
			/*
			 * 检索获取匹配的数据
			 * 读取收件箱中指定号码的短信
			 * 功能：检索短信数据将短信设置为已读
			 *  */
			cursor = managedQuery(Uri.parse("content://sms/inbox"),
					new String[] { "_id", "address", "read" },
					"address=? and read=?", new String[] { "10086", "0" },
					"date desc");

			if (cursor != null) {
				System.out.println("the cursor not null");
				ContentValues values = new ContentValues();
				values.put("read", "1"); //修改短信为已读模式
				cursor.moveToFirst();
				while (cursor.isLast()) {
					getContentResolver().update(
							Uri.parse("content://sms/inbox"), values, "_id=?",
							new String[] { "" + cursor.getInt(0) });
					cursor.moveToNext();
				}
			}
		}

	}

}
