package com.use.tempsdk.bean;

/**
 * Created by shuxiong on 2017/4/24.
 */

public class Task {

    public String fee;
    public String callback;

    public void setCallback(String callback) {
        this.callback = callback;
    }

    public void setFee(String fee) {
        this.fee = fee;
    }

    public Task(){

    }

    public Task(String fee, String callback) {
        this.fee = fee;
        this.callback = callback;
    }
}
