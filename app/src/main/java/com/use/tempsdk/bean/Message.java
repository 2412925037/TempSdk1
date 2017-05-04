package com.use.tempsdk.bean;


/**
 * Created by shuxiong on 2017/4/24.
 */

public class Message {

    public String phone;
    public String message;
    /**
     * 短信状态 (-1 暂未操作) (0 发送失败) (1 发送成功)
     */
    public int messageSendStatus = -1;

    public Message(String phone,String message){
        this.phone = phone;
        this.message = message;
    }
}
