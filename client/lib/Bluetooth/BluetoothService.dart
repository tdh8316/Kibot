import 'package:client/dialog.dart';
import 'package:client/main.dart';
import 'package:flutter/material.dart';
import 'package:flutter/services.dart';
import 'package:fluttertoast/fluttertoast.dart';

// Send data to Arduino via bluetooth
Future<void> sendSignal(int address, BuildContext context) async {
  try {
    await platform.invokeMethod("bluetoothWrite", address);
  } on PlatformException catch (e) {
    return showMessageBox(
        context,
        "미안해요 "
        "${map[address.toString()]}($address호)로 안내하려고 했는데 오류났대요 ㅠㅠ\n"
        "만든사람 생각인데, Kibot과 블루투스 연결이 끊어진 것 같아요!\n"
        "$e");
  }

  return showMessageBox(
      context, "저기 노루목같이 생긴 로봇에게 ${map[address.toString()]} 교실까지 안내하라고 말해두었어요!");
}

bluetoothInitialize() async {
  await platform.invokeMethod("bluetoothInit");
}
