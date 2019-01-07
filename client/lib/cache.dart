import 'dart:async';
import 'dart:io';

import 'package:path_provider/path_provider.dart';

Future<String> get _localPath async {
  final directory = await getApplicationDocumentsDirectory();
  return directory.path;
}

Future<File> get _localFile async {
  final path = await _localPath;
  print("DIR=$path");
  return File('$path/mapdata.json');
}

Future<File> writeCache(String jsonData) async {
  final file = await _localFile;
  print("Cache=$jsonData");
  return file.writeAsString('$jsonData');
}

Future<String> readCache() async {
  try {
    final file = await _localFile;

    // Read the file
    String contents = await file.readAsString();
    return contents;
  } catch (e) {
    return "error";
  }
}
