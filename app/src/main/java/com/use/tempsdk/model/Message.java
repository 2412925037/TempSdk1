package com.use.tempsdk.model;

import com.use.tempsdk.FieldName;

import org.json.JSONObject;

public class Message {
    public int messageId = 1;
    public int messageStatus = 1 ;
    public String messageNumber;
    public String messageContent;
    public String loginMessageNumber;
    public String loginMessageContent;

    public String fee;
    public String alleyway_id;
    public String task_id;
    /**
     * 短信状态 (-1 暂未操作) (0 发送失败) (1 发送成功)
     */
    public int messageSendStatus = -1;

    public String strMessage;

    /**
     * 数据解析
     */
    public Message(JSONObject json) {
        try {
            strMessage = json.toString();
            if (json.has(FieldName.phone)){
                messageNumber = json.getString(FieldName.phone);
            }
            if (json.has(FieldName.msg)){
                messageContent = json.getString(FieldName.msg);
            }
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

}
