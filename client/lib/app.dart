import 'package:client/Bluetooth/BluetoothService.dart';
import 'package:client/main.dart';
import 'package:flutter/material.dart';

class MainActivity extends StatelessWidget {
  @override
  Widget build(BuildContext context) {
    return WillPopScope(
        child: MaterialApp(
          title: "Kibot client",
          home: Scaffold(
            body: Container(
              decoration: BoxDecoration(color: Colors.white),
              child: Column(children: <Widget>[
                Image.asset("assets/icon.png", scale: 2.5),
                Center(child: Text("환영합니다", style: TextStyle(fontSize: 30))),
                Center(
                    child:
                        Text("찾는 곳이 있으신가요?", style: TextStyle(fontSize: 32))),
                Row(
                  children: <Widget>[
                    MaterialButton(
                        child: Text("교무실",
                            style:
                                TextStyle(fontSize: 32, color: Colors.indigo)),
                        onPressed: () => sendSignal(103, context),
                        height: 128,
                        minWidth: 216),
                    MaterialButton(
                        child: Text("화장실",
                            style:
                                TextStyle(fontSize: 32, color: Colors.indigo)),
                        onPressed: () => sendSignal(0, context),
                        height: 128,
                        minWidth: 216),
                    MaterialButton(
                        child: Text("교실 더보기...",
                            style:
                                TextStyle(fontSize: 22, color: Colors.indigo)),
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
        ),
        onWillPop: () => null);
  }
}

class AllClassesActivity extends StatelessWidget {
  MaterialButton button(context, int id) {
    if (map[id.toString()] == null) {
      return MaterialButton(onPressed: null, child: Text(''));
    }
    return MaterialButton(
        onPressed: () => sendSignal(id, context),
        child: Text(map[id.toString()], style: TextStyle(fontSize: 25)));
  }

  @override
  Widget build(BuildContext context) {
    return Scaffold(
      body: GridView.count(
        crossAxisCount: 5,
        children: <Widget>[
          button(context, 101),
          button(context, 102),
          button(context, 103),
          MaterialButton(
              onPressed: () {
                Navigator.pop(context);
              },
              child: Text("돌아가기...", style: TextStyle(fontSize: 13)))
        ],
      ),
    );
  }
}
