pytjs
=====

About
-----

This repository contains a Python interface to TJS2.

Installation (from PyPI)
------------------------

.. code:: bash

   python3 -m pip install pytjs

Installation (from source)
--------------------------

First, clone this repository, including all submodules.

.. code:: bash

   git clone --recursive https://github.com/uyjulian/pytjs.git

Now, you can run ``pip install`` on the repository path.

.. code:: bash

   python3 -m pip install ./pytjs

Usage
-----

Firstly, you need to initialize a TJS script engine.

.. code:: py

   import pytjs

   ScriptEngine = pytjs.tTJS()

You can then get things in its global environment.

.. code:: py

   ScriptEngineGlobal = ScriptEngine.GetGlobal()
   print(ScriptEngineGlobal.Dictionary) # <tTJSDispatch2Wrapper 0x7ffcd1c271f0:0x0>
   # or
   print(ScriptEngineGlobal['Dictionary']) # <tTJSDispatch2Wrapper 0x7ffcd1c271f0:0x0>

You can also set values in the global environment.

.. code:: py

   ScriptEngineGlobal = ScriptEngine.GetGlobal()
   ScriptEngineGlobal.test = "test"
   # or
   ScriptEngineGlobal["test"] = "test"

You can evaluate expressions in the script engine environment.

.. code:: py

   print(ScriptEngine.EvalExpression("123")) # 123
   # 123

You can iterate through Array and Dictionary objects.

.. code:: py

   arr = ScriptEngine.EvalExpression("['test', 'test2']")
   for v in arr:
       print(v)
   # test
   # test2
   dic = ScriptEngine.EvalExpression("%['test' => 'test2']")
   for v in dic:
       print(v, dic[v])
   # test
   # test2

License
-------

This project is licensed under the MIT license. Please read the
``LICENSE`` file for more information.
