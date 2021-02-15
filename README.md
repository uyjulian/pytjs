# pytjs

## About

This repository contains a Python interface to TJS2.  

## Installation

First, clone this repository, including all submodules.  
```bash
git clone --recursive https://github.com/uyjulian/pytjs.git
```
Now, you can run `pip install` on the repository path.  
```bash
pip install ./pytjs
```

## Usage

Firstly, you need to initialize a TJS script engine.  
```py
import pytjs

ScriptEngine = pytjs.tTJS()
```
You can then get things in its global environment.  
```py
ScriptEngineGlobal = ScriptEngine.GetGlobal()
print(ScriptEngineGlobal.Dictionary) # <tTJSDispatch2Wrapper 0x7ffcd1c271f0:0x0>
# or
print(ScriptEngineGlobal['Dictionary']) # <tTJSDispatch2Wrapper 0x7ffcd1c271f0:0x0>
```
You can also set values in the global environment.  
```py
ScriptEngineGlobal = ScriptEngine.GetGlobal()
ScriptEngineGlobal.test = "test"
# or
ScriptEngineGlobal["test"] = "test"
```
You can evaluate expressions in the script engine environment.  
```py
print(ScriptEngine.EvalExpression("123")) # 123
# 123
```

## License

This project is licensed under the MIT license. Please read the `LICENSE` file for more information.
