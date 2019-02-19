package com.tdh8316.kibot.client;

import android.annotation.SuppressLint;
import android.os.Bundle;
import android.support.v7.app.AppCompatActivity;
import android.text.method.ScrollingMovementMethod;
import android.widget.TextView;

public class LogActivity extends AppCompatActivity {
    @SuppressLint("SetTextI18n")
    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_log);
        TextView tv = findViewById(R.id.textView);
        tv.setMovementMethod(new ScrollingMovementMethod());

        tv.setText("LOG STARTED\n");

        /*tv.setText("Loading...");
        try {
            Process process = Runtime.getRuntime().exec("logcat -E");
            BufferedReader bufferedReader = new BufferedReader(new InputStreamReader(process.getInputStream()));

            StringBuilder log = new StringBuilder();
            String line;
            while ((line = bufferedReader.readLine()) != null) {
                log.append(line);
            }
            tv.setText(tv.getText().toString() + log.toString());
        } catch (IOException e) {
            // tv.setText(e.toString());
        }*/
    }
}
