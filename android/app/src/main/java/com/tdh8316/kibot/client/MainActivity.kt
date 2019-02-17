package com.tdh8316.kibot.client

import android.app.AlertDialog
import android.bluetooth.BluetoothDevice
import android.content.Intent
import android.content.pm.ActivityInfo
import android.os.Bundle
import android.speech.RecognitionListener
import android.speech.RecognizerIntent
import android.speech.SpeechRecognizer
import android.support.v7.app.AppCompatActivity
import android.util.Log
import android.view.WindowManager
import kotlinx.android.synthetic.main.activity_main.*
import me.aflak.bluetooth.Bluetooth
import me.aflak.bluetooth.DiscoveryCallback
import java.io.File
import java.lang.Exception
import java.util.*


class MainActivity : AppCompatActivity() {

    private var bluetooth: Bluetooth = Bluetooth(this)

    private val mSpeechRecognizer = SpeechRecognizer.createSpeechRecognizer(this)
    private val mSpeechRecognizerIntent = Intent(RecognizerIntent.ACTION_RECOGNIZE_SPEECH)

    override fun onCreate(savedInstanceState: Bundle?) {
        val initThread = Thread {
            initClassInfo(
                File(
                    "${getExternalFilesDir(null)}",
                    "classes.json"
                )
            )
        }
        initThread.start()

        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main)
        requestedOrientation = ActivityInfo.SCREEN_ORIENTATION_LANDSCAPE
        window.setFlags(WindowManager.LayoutParams.FLAG_LAYOUT_NO_LIMITS, 512)
        window.addFlags(WindowManager.LayoutParams.FLAG_SHOW_WALLPAPER)
        window.addFlags(524288) // FLAG_SHOW_WHEN_LOCKED

        initBluetooth()
        initSpeechRecognizer()

        initThread.join()

        mic.setOnClickListener {
            Log.d(MainActivity::class.java.name, "Listener is started.")
            mic.setImageResource(R.drawable.ic_mic_black_24dp)
            mSpeechRecognizer.startListening(mSpeechRecognizerIntent)
        }
    }

    private fun initSpeechRecognizer() {
        mSpeechRecognizerIntent.putExtra(
            RecognizerIntent.EXTRA_LANGUAGE,
            Locale.getDefault()
        )

        mSpeechRecognizer.setRecognitionListener(object : RecognitionListener {
            override fun onReadyForSpeech(bundle: Bundle) {}
            override fun onBeginningOfSpeech() {}
            override fun onRmsChanged(v: Float) {}
            override fun onBufferReceived(bytes: ByteArray) {}
            override fun onEndOfSpeech() {}
            override fun onPartialResults(bundle: Bundle) {}
            override fun onEvent(i: Int, bundle: Bundle) {}
            override fun onError(err: Int) {
                val errorMessage: String = when (err) {
                    SpeechRecognizer.ERROR_SPEECH_TIMEOUT ->
                        "제가 참을성이 없어서 이렇게 길게는 못듣겠네요 ><"
                    SpeechRecognizer.ERROR_SERVER, SpeechRecognizer.ERROR_NETWORK_TIMEOUT ->
                        "네트워크 오류"
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
                val m = result.getStringArrayList(SpeechRecognizer.RESULTS_RECOGNITION)!![0]
                val id = getId(
                    getObject(
                        m
                    )
                )
                if (id == null) {
                    showDialog("$m => 정의되지 않음")
                } else {
                    sendToKibot(
                        id
                    )
                }
                mic.setImageResource(R.drawable.ic_mic_black_24dp)
            }
        })
    }

    private fun initBluetooth() {
        try {
            bluetooth.onStart()
            bluetooth.enable()
            bluetooth.setDiscoveryCallback(object : DiscoveryCallback {
                override fun onDiscoveryStarted() {}
                override fun onDiscoveryFinished() {}
                override fun onDeviceUnpaired(device: BluetoothDevice) {}
                override fun onError(message: String) {}
                override fun onDeviceFound(device: BluetoothDevice) {}
                override fun onDevicePaired(device: BluetoothDevice) {}
            })
            bluetooth.connectToName(KIBOT_BLUETOOTH_NAME)
            val devices = bluetooth.pairedDevices
            val device = devices[0]
            device.createBond()
            device.setPin(byteArrayOf(KIBOT_BLUETOOTH_PIN.toByte()))
            bluetooth.connectToDevice(device)
        } catch (e: Exception) {
            showDialog("Kibot 과 연결할 수 없습니다!!!")
        }
    }

    private fun sendToKibot(id: Int?) {
        if (!bluetooth.isConnected) {
            showDialog("└(๑•Kibot 과 연결되어있지 않아요...•́๑)┐")
        } else {
            if (id == null) {
                return
            }
            Log.d("ID", "$id")
            bluetooth.send("$id")
        }
    }

    private fun showDialog(msg: String, title: String = "강원중학교 안내봇") {
        val builder = AlertDialog.Builder(this)
        builder.setTitle(title)
        builder.setMessage(msg)
        builder.setPositiveButton("확인", null)
        builder.show()
    }

    override fun onStop() {
        super.onStop()
        bluetooth.onStop()
    }

    override fun onBackPressed() {
        return
    }

    override fun onUserLeaveHint() {
        // INFO: DO NOT EDIT THIS SECTION
        // startActivity(Intent(this, MainActivity::class.java))
    }
}
