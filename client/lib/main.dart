import 'package:flutter/material.dart';
import 'package:flutter/services.dart';
import 'package:fluttertoast/fluttertoast.dart';

const platform = const MethodChannel("Kibot/client");

void main() {
  runApp(new MaterialApp(home: MainActivity()));
}

void showToast(msg) {
  Fluttertoast.showToast(
      msg: msg,
      toastLength: Toast.LENGTH_SHORT,
      gravity: ToastGravity.BOTTOM,
      backgroundColor: Colors.indigo,
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
        title: Text("Something to tell..."),
        content: Text(msg),
        actions: <Widget>[
          // usually buttons at the bottom of the dialog
          FlatButton(
            child: Text("Close"),
            onPressed: () {
              Navigator.of(context).pop();
            },
          ),
        ],
      );
    },
  );
}

bool showQuestionDialog(context, msg) {
  // TODO: May I help you?
  return false;
}

Future<void> sendSignal(String s, BuildContext context) async {
  try {
    await platform.invokeMethod("bluetoothWrite", s);
  } on PlatformException catch (e) {
    return showMessageBox(context, "Failed to write via bluetooth. $e");
  }

  return showMessageBox(context, "앞의 노루목같이 생긴 로봇에게 $s 교실까지 안내하라고 말해두었어요!");
}

class MainActivity extends StatelessWidget {
  bluetoothInitialize(context) async {
    try {
      await platform.invokeMethod("bluetoothInit");
    } on PlatformException catch (e) {
      return showMessageBox(context, "Failed to initialize bluetooth. $e");
    }
    return showToast("Bluetooth initialized successfully.");
  }

  @override
  Widget build(BuildContext context) {
    // Initialize bluetooth
    bluetoothInitialize(context);
    // Remove all overlaid system ui
    SystemChrome.setEnabledSystemUIOverlays([]);
    return MaterialApp(
      title: "Kibot client",
      home: Scaffold(
        body: Container(
          decoration: BoxDecoration(color: Colors.white),
          child: Column(children: <Widget>[
            Image.asset("assets/icon.png", scale: 2.5),
            Center(child: Text("환영합니다", style: TextStyle(fontSize: 30))),
            Center(child: Text("찾는 곳이 있으신가요?", style: TextStyle(fontSize: 32))),
            Row(
              children: <Widget>[
                MaterialButton(
                    child: Text("교무실",
                        style: TextStyle(fontSize: 32, color: Colors.indigo)),
                    onPressed: () => sendSignal("교무실", context),
                    height: 128,
                    minWidth: 216),
                MaterialButton(
                    child: Text("화장실",
                        style: TextStyle(fontSize: 32, color: Colors.indigo)),
                    onPressed: () => sendSignal("화장실", context),
                    height: 128,
                    minWidth: 216),
                MaterialButton(
                    child: Text("교실 더보기...",
                        style: TextStyle(fontSize: 22, color: Colors.indigo)),
                    onPressed: () {
                      Navigator.push(
                          context,
                          MaterialPageRoute(
                              builder: (context) => AllClassesActivity()));
                    })
              ],
            )
          ]),
        ),
      ),
    );
  }
}

class AllClassesActivity extends StatelessWidget {
  @override
  Widget build(BuildContext context) {
    return Scaffold(
      body: GridView.count(
        crossAxisCount: 5,
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
          MaterialButton(
              onPressed: () {
                Navigator.pop(context);
              },
              child: Text("돌아가기...", style: TextStyle(fontSize: 25)))
        ],
      ),
    );
  }
}
