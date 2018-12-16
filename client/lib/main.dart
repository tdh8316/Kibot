import 'package:flutter/material.dart';
import 'package:flutter/services.dart';
import 'package:fluttertoast/fluttertoast.dart';

const platform = const MethodChannel("Kibot/client");

void main() {
  try {
    platform.invokeMethod("bluetoothInit");
  } catch (e) {}
  runApp(new MaterialApp(home: MainActivity()));
}

void showToast(msg) {
  Fluttertoast.showToast(
      msg: msg,
      toastLength: Toast.LENGTH_SHORT,
      gravity: ToastGravity.BOTTOM,
      backgroundColor: Colors.red,
      textColor: Colors.white,
      timeInSecForIos: 1);
}

void showMessageBox(context, msg) {
  // flutter defined function
  showDialog(
    context: context,
    builder: (BuildContext context) {
      // return object of type Dialog
      return AlertDialog(
        title: new Text("Something to tell..."),
        content: new Text(msg),
        actions: <Widget>[
          // usually buttons at the bottom of the dialog
          new FlatButton(
            child: new Text("Close"),
            onPressed: () {
              Navigator.of(context).pop();
            },
          ),
        ],
      );
    },
  );
}

class MainActivity extends StatelessWidget {
  sendSignal(String s, BuildContext context) {
    platform.invokeMethod("bluetoothWrite", s);
    showMessageBox(context, "앞의 노루목같이 생긴 로봇에게 $s 교실까지 안내하라고 말해두었어요!");
    //showMessageBox(context, "Failed to write via bluetooth");
  }

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
                  onPressed: () => sendSignal("교무실", context),
                  child: Text("교무실", style: TextStyle(fontSize: 25))),
              MaterialButton(
                  onPressed: () => sendSignal("화장실", context),
                  child: Text("화장실", style: TextStyle(fontSize: 25))),
              MaterialButton(
                  onPressed: () => sendSignal("엄재훈 선생님", context),
                  child: Text("엄재훈", style: TextStyle(fontSize: 25))),
            ],
          )),
    );
  }
}
