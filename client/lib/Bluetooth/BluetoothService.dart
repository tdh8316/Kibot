import 'package:client/interaction.dart';
import 'package:client/main.dart';
import 'package:flutter/material.dart';
import 'package:flutter/services.dart';

// Send data to Arduino via bluetooth
Future<void> sendSignal(int address, BuildContext context) async {
  try {
    await platform.invokeMethod("bluetoothWrite", address);
  } on PlatformException catch (e) {
    return showMessageBox(
        context,
        "Failed to write via bluetooth."
        "(adr=$address)(tch=${map[address.toString()]}) $e");
  }

  return showMessageBox(
      context, "앞의 노루목같이 생긴 로봇에게 ${map[address]} 교실까지 안내하라고 말해두었어요!");
}

bluetoothInitialize(context) async {
  try {
    await platform.invokeMethod("bluetoothInit");
  } on PlatformException catch (e) {
    return showMessageBox(context, "Failed to initialize bluetooth. $e");
  }
  return showToast("Bluetooth initialized successfully.");
}
