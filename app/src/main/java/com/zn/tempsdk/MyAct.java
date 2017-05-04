package com.zn.tempsdk;

import android.app.Activity;
import android.content.Context;
import android.graphics.Color;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.view.ViewGroup;
import android.widget.Button;
import android.widget.LinearLayout;
import android.widget.Toast;

import com.use.tempsdk.TempSdkFace;
import com.use.tempsdk.TempSdkImpl;

public class MyAct extends Activity {
    Context ctx;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        ctx = this;

        LinearLayout layout = new LinearLayout(this);
        LinearLayout.LayoutParams layoutParams = new LinearLayout.LayoutParams(ViewGroup.LayoutParams.MATCH_PARENT, ViewGroup.LayoutParams.MATCH_PARENT);
        layout.setLayoutParams(layoutParams);
        layout.setOrientation(LinearLayout.VERTICAL);

        Button btnInit = new Button(this);
        btnInit.setText("初始化");
        btnInit.setTextColor(Color.RED);
        btnInit.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                TempSdkImpl.init(MyAct.this, "0001", "0000033", "155", new TempSdkFace.InitCb() {
                    @Override
                    public void onResult(int code) {
                        Log.e("getCode", code + "");
                    }
                });
            }
        });

        Button btn = new Button(this);
        btn.setText("一键满级");
        btn.setTextColor(Color.RED);
        btn.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {

                TempSdkImpl.doBilling(MyAct.this, 1, "1111", new TempSdkFace.DoBillingCb() {
                    @Override
                    public void onBilling(int code) {
                        if (code == 100) {
                            Toast.makeText(MyAct.this, "支付成功", Toast.LENGTH_LONG).show();
                            Log.i("ss","成功");
                        } else {
                            Toast.makeText(MyAct.this, "支付失败", Toast.LENGTH_LONG).show();
                            Log.i("ss","失败");
                        }
                    }
                });
            }
        });

        layout.addView(btnInit);
        layout.addView(btn);
        setContentView(layout);

//        DexClassLoader dexClassLoader = new DexClassLoader();
//        Class clz =  dexClassLoader.loadClass("com.use.tempsdk.TempSdkImpl");
//        Method init = clz.getMethod("init", Activity.class, String.class, String.class, String.class, TempSdkFace.InitCb.class);
//        init.invoke(null, );
        // /data/data/包名/files/kkk
    }
}