import 'dart:convert';

import 'package:client/app.dart';
import 'package:flutter/material.dart';
import 'package:flutter/services.dart';
import 'package:http/http.dart' as http;

const platform = const MethodChannel("Kibot/client");
Map<String, dynamic> map;

void main() async {
  final response = await http.get("https://raw.githubusercontent.com/"
      "tdh8316/Kibot/master/"
      "client/share/test.json"
  );
  if (response.statusCode != 200) throw Exception("Failed to access master/client/share/map.json");

  debugPrint(response.body);
  map = json.decode(response.body);
  runApp(new MaterialApp(home: MainActivity()));
}
