package com.takturstudio.tdh8316.kibot.client

import android.Manifest
import android.content.ComponentName
import android.content.Intent
import android.content.pm.PackageManager
import android.os.Bundle
import android.speech.RecognitionListener
import android.speech.RecognizerIntent
import android.speech.SpeechRecognizer
import android.util.Log
import androidx.appcompat.app.AlertDialog
import androidx.appcompat.app.AppCompatActivity
import androidx.core.app.ActivityCompat
import kotlinx.android.synthetic.main.activity_main.*
import java.util.*
import kotlin.system.exitProcess


class MainActivity : AppCompatActivity() {

    private val mSpeechRecognizer = SpeechRecognizer.createSpeechRecognizer(
        this
    )
    private val mSpeechRecognizerIntent = Intent(RecognizerIntent.ACTION_RECOGNIZE_SPEECH)


    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main)

        buttonListening.setOnClickListener {
            mSpeechRecognizer.startListening(mSpeechRecognizerIntent)
        }

        requestPermissions()
        initSpeechRecognizer()
    }

    private fun requestPermissions() {
        ActivityCompat.requestPermissions(
            this,
            arrayOf(
                Manifest.permission.INTERNET,
                Manifest.permission.RECORD_AUDIO
            ),
            PERMISSION_REQUEST_CODE
        )
    }

    override fun onRequestPermissionsResult(requestCode: Int, permissions: Array<out String>, grantResults: IntArray) {
        if (requestCode != PERMISSION_REQUEST_CODE
            || grantResults.isEmpty()
            || grantResults[0] == PackageManager.PERMISSION_DENIED
        ) {
            exitProcess(-1)
        }
    }

    private fun initSpeechRecognizer() {
        mSpeechRecognizerIntent.putExtra(
            RecognizerIntent.EXTRA_LANGUAGE,
            Locale.getDefault()
        )

        mSpeechRecognizer.setRecognitionListener(object : RecognitionListener {
            override fun onReadyForSpeech(bundle: Bundle) {

            }

            override fun onBeginningOfSpeech() {

            }

            override fun onRmsChanged(v: Float) {

            }

            override fun onBufferReceived(bytes: ByteArray) {

            }

            override fun onEndOfSpeech() {

            }

            override fun onError(err: Int) {
                val errorMessage: String = when (err) {
                    SpeechRecognizer.ERROR_SPEECH_TIMEOUT ->
                        "제가 참을성이 없어서 이렇게 길게는 못듣겠네요 ><"
                    SpeechRecognizer.ERROR_SERVER, SpeechRecognizer.ERROR_NETWORK_TIMEOUT ->
                        "앗 갑자기 귀가 안들려엇..."
                    SpeechRecognizer.ERROR_AUDIO ->
                        "오류: 오디오 녹음 실패"
                    SpeechRecognizer.ERROR_RECOGNIZER_BUSY ->
                        "이미 듣고 있는데요옹 ??"
                    SpeechRecognizer.ERROR_NO_MATCH ->
                        "무슨말인지 잘 모르겠어요 ㅠㅠ"
                    else ->
                        "└(๑•̀o•́๑)┐ 상상도 못한 오류! 코드 $err."
                }

                AlertDialog.Builder(this@MainActivity).setTitle("")
                    .setMessage(errorMessage).setPositiveButton("확인")
                    { _, _ -> }.show()
            }

            override fun onResults(result: Bundle) {
                //getting all the matches
                val matches = result
                    .getStringArrayList(SpeechRecognizer.RESULTS_RECOGNITION)

                Log.d(LOG_SPEECH_RECOGNIZE, matches?.toString())
            }

            override fun onPartialResults(bundle: Bundle) {

            }

            override fun onEvent(i: Int, bundle: Bundle) {

            }
        })
    }
}
