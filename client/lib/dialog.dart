import 'package:flutter/material.dart';
import 'package:fluttertoast/fluttertoast.dart';

void showToast(msg, {length = Toast.LENGTH_SHORT}) {
  Fluttertoast.showToast(
      msg: msg,
      toastLength: length,
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
  // TODO: Asking dialog
  return false;
}
