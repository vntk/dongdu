{
    "targets": [
        {
            "target_name": "dongdu",
            "sources": [
                "src/dongdu.cc",
                "src/DicMap.cpp",
                "src/Feats.cpp",
                "src/FeaturesSelection.cpp",
                "src/Machine.cpp",
                "src/Predictor.cc",
                "src/StrMap.cpp",
                "src/SylMap.cpp",
                "src/liblinear/linear.cpp",
                "src/liblinear/tron.cpp",
                "src/liblinear/tron.cpp",
                "src/liblinear/blas/daxpy.c",
                "src/liblinear/blas/ddot.c",
                "src/liblinear/blas/dnrm2.c",
                "src/liblinear/blas/dscal.c",
            ],
            "include_dirs": [
                "<!(node -e \"require('nan')\")"
            ]
        },
        {
            "target_name": "action_after_build",
            "type": "none",
            "dependencies": [ "<(module_name)" ],
            "copies": [{
                "files": [ "<(PRODUCT_DIR)/<(module_name).node" ],
                "destination": "<(module_path)"
            }]
        }
    ]
}