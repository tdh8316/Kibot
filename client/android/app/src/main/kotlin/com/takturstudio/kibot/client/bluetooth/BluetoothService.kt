package com.takturstudio.kibot.client.bluetooth


import android.annotation.TargetApi
import android.bluetooth.BluetoothAdapter
import android.bluetooth.BluetoothDevice
import android.os.Build
import android.util.Log
import java.io.IOException
import java.io.InputStream
import java.io.OutputStream

class BluetoothService {
    private var outputStream: OutputStream? = null
    private var inStream: InputStream? = null
    private val position: Int = 0
    @TargetApi(Build.VERSION_CODES.KITKAT)
    @Throws(IOException::class)
    fun init() {
        val blueAdapter = BluetoothAdapter.getDefaultAdapter()
        if (blueAdapter != null) {
            if (blueAdapter.isEnabled) {
                val bondedDevices = blueAdapter.bondedDevices
                if (bondedDevices.size > 0) {
                    val devices = bondedDevices.toTypedArray() as Array<*>
                    val device = devices[position] as BluetoothDevice
                    val uuids = device.uuids
                    val socket = device.createRfcommSocketToServiceRecord(uuids[0].uuid)
                    socket.connect()
                    outputStream = socket.outputStream
                    inStream = socket.inputStream
                }
                Log.e("error", "No appropriate paired devices.")
            } else {
                Log.e("error", "Bluetooth is disabled.")
            }
        }
    }

    @Throws(IOException::class)
    fun write(s: String) {
        outputStream!!.write(s.toByteArray())
    }

    fun run() {
        val size = 1024
        val buffer = ByteArray(size)
        var bytes = 0
        while (true) {
            try {
                bytes = inStream!!.read(buffer, bytes, size - bytes)
            } catch (e: IOException) {
                e.printStackTrace()
            }
        }
    }
}
