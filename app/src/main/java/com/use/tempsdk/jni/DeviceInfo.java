package com.use.tempsdk.jni;

import android.content.Context;

/**
 * Created by shuxiong on 2017/4/18.
 */

public class DeviceInfo {

    public native static String message(Context context,String pid,String channelid,String gameid);
        static {
        System.loadLibrary("device-info");
    }
}
