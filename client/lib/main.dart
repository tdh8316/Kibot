import 'package:flutter/material.dart';
import 'package:flutter/services.dart';
import 'package:fluttertoast/fluttertoast.dart';

const platform = const MethodChannel("Kibot/client");

void main() {
  try {
    platform.invokeMethod("bluetoothInit");
    runApp(new MaterialApp(home: MainActivity()));
  } catch (e) {
    showToast("FATAL: $e");
  }
}

void showToast(msg) {
  Fluttertoast.showToast(
      msg: msg,
      toastLength: Toast.LENGTH_SHORT,
      gravity: ToastGravity.TOP,
      backgroundColor: Colors.red,
      textColor: Colors.white,
      timeInSecForIos: 1);
}

class MainActivity extends StatelessWidget {
  @override
  Widget build(BuildContext context) {
    return new MaterialApp(
      title: "Kibot client",
      home: Scaffold(
          appBar: AppBar(
            title: Text("어디를 찾아 오셨나요?"),
          ),
          body: GridView.count(
            crossAxisCount: 3,
            padding: EdgeInsets.all(5),
            children: <Widget>[
              MaterialButton(
                  onPressed: () =>
                      platform.invokeMethod("bluetoothWrite", "교무실"),
                  child: Text("교무실", style: TextStyle(fontSize: 25))),
              MaterialButton(
                  onPressed: () =>
                      platform.invokeMethod("bluetoothWrite", "화장실"),
                  child: Text("화장실", style: TextStyle(fontSize: 25))),
              MaterialButton(
                  onPressed: () =>
                      platform.invokeMethod("bluetoothWrite", "엄재훈"),
                  child: Text("엄재훈", style: TextStyle(fontSize: 25))),
            ],
          )),
    );
  }
}
