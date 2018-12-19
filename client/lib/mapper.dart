import 'dart:async';
import 'dart:convert';

import 'package:http/http.dart' as http;

// TODO: fetch json from git
Future<http.Response> fetch() async {
  final response = await http.get("https://raw.githubusercontent.com/"
      "tdh8316/Kibot/master/"
      "client/share/test.json");

  if (response.statusCode == 200) {
    return json.decode(response.body);
  } else {
    throw Exception("Failed to access master/client/share/map.json");
  }
}

final tmpMap = {
  // 으어어ㅓ어엉 인터넷에서 받아오기는 왜 안되는거냐여ㅑ린요ㅑㅎ
  101: "엄재훈 선생님",
  102: "황은경 선생님",
  103: "교무실",
};
