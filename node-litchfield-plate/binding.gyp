{
  "targets": [
    {
      "target_name": "plate",
      "sources": [ "plate.cc", "../calc_plate/alignment.cpp" ],
      "include_dirs": [
        "<!(node -e \"require('nan')\")"
      ],
      "cflags": [
        "-std=c++11"
      ]
    }
  ]
}
