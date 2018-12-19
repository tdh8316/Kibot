import 'package:client/app.dart';
import 'package:client/mapper.dart';
import 'package:flutter/material.dart';
import 'package:flutter/services.dart';

const platform = const MethodChannel("Kibot/client");
final Map<int, String> map = tmpMap;

void main() {
  runApp(new MaterialApp(home: MainActivity()));
}
