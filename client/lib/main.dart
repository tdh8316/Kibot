import 'dart:convert';

import 'package:client/app.dart';
import 'package:client/cache.dart';
import 'package:flutter/material.dart';
import 'package:flutter/services.dart';
import 'package:http/http.dart' as http;

const platform = const MethodChannel("Kibot/client");
Map<String, dynamic> map;
String mapData;

void main() async {
  try {
    final response = await http.get("https://raw.githubusercontent.com/"
        "tdh8316/Kibot/master/client/share/test.json");
    mapData = response.body;
    writeCache(mapData);
  } on Exception {
    print("Failed to connect");
    mapData = await readCache();
    if (mapData == "error") {
      throw Exception("Failed to read mapdata.json");
    }
  }
  print(mapData);
  map = json.decode(mapData);

  // Remove all overlaid system ui
  SystemChrome.setEnabledSystemUIOverlays([]);
  // Locking the screen landscape
  SystemChrome.setPreferredOrientations(
      [DeviceOrientation.landscapeRight, DeviceOrientation.landscapeLeft]);

  runApp(MaterialApp(home: MainActivity()));
}
