package com.example.matt.sortdemo;

import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;

public class SortDemoActivity extends AppCompatActivity {

    SortDemoView mView;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        mView = new SortDemoView(getApplication());
        setContentView(mView);
    }

    @Override protected void onPause() {
        super.onPause();
        mView.onPause();
    }

    @Override protected void onResume() {
        super.onResume();
        mView.onResume();
    }
}
