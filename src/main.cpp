#include <pybind11/pybind11.h>
#include "tjsCommHead.h"
#include "tjs.h"
#include "tjsArray.h"
#include "TextStream.h"
#include "StorageImpl.h"
#include "CharacterSet.h"
#include "DebugIntf.h"

#define STRINGIFY(x) #x
#define MACRO_STRINGIFY(x) STRINGIFY(x)

namespace py = pybind11;

static py::object tjs_variant_to_py_object(tTJSVariant v);
static tTJSVariant py_object_to_tjs_variant(py::object v);

static py::str ttstr_to_pystr(ttstr v)
{
    return py::str(py::cast(v.AsStdString()));
}


class iTJSDispatch2WrapperForPython : public tTJSDispatch
{
    public: iTJSDispatch2WrapperForPython(py::object v)
    {
        this->v = v;
    }
    
    public: ~iTJSDispatch2WrapperForPython() {}

    public: tjs_error TJS_INTF_METHOD CreateNew(tjs_uint32 flag, const tjs_char * membername, tjs_uint32 *hint, iTJSDispatch2 **result, tjs_int numparams, tTJSVariant **param, iTJSDispatch2 *objthis)
    {
        py::list temp_array;
        for (tjs_int i = 0; i < numparams; i += 1)
        {
            temp_array.append(tjs_variant_to_py_object(*param[i]));
        }
        py::object func_to_call = v;
        if (membername)
        {
            func_to_call = v[ttstr_to_pystr(membername)];
        }
        py::tuple temp_tuple(temp_array);
        *result = py_object_to_tjs_variant(func_to_call(*temp_tuple));
        return TJS_S_OK;
    }

    public: tjs_error TJS_INTF_METHOD FuncCall(tjs_uint32 flag, const tjs_char * membername, tjs_uint32 *hint, tTJSVariant *result, tjs_int numparams, tTJSVariant **param, iTJSDispatch2 *objthis)
    {
        py::list temp_array;
        for (tjs_int i = 0; i < numparams; i += 1)
        {
            temp_array.append(tjs_variant_to_py_object(*param[i]));
        }
        py::object func_to_call = v;
        if (membername)
        {
            func_to_call = v[ttstr_to_pystr(membername)];
        }
        py::tuple temp_tuple(temp_array);
        *result = py_object_to_tjs_variant(func_to_call(*temp_tuple));
        return TJS_S_OK;
    }

    public: tjs_error TJS_INTF_METHOD FuncCallByNum(tjs_uint32 flag, tjs_int num, tTJSVariant *result, tjs_int numparams, tTJSVariant **param, iTJSDispatch2 *objthis)
    {
        py::list temp_array;
        for (tjs_int i = 0; i < numparams; i += 1)
        {
            temp_array.append(tjs_variant_to_py_object(*param[i]));
        }
        py::object func_to_call = v[py::int_(num)];
        py::tuple temp_tuple(temp_array);
        *result = py_object_to_tjs_variant(func_to_call(*temp_tuple));
        return TJS_S_OK;
    }

    public: tjs_error TJS_INTF_METHOD PropGet(tjs_uint32 flag, const tjs_char * membername, tjs_uint32 *hint, tTJSVariant *result, iTJSDispatch2 *objthis)
    {
        if (!membername)
        {
            return TJS_E_NOTIMPL;
        }
        *result = py_object_to_tjs_variant(v[ttstr_to_pystr(membername)]);
        return TJS_S_OK;
    }

    public: tjs_error TJS_INTF_METHOD PropGetByNum(tjs_uint32 flag, tjs_int num, tTJSVariant *result, iTJSDispatch2 *objthis)
    {
        *result = py_object_to_tjs_variant(v[py::int_(num)]);
        return TJS_S_OK;
    }

    public: tjs_error TJS_INTF_METHOD PropSet(tjs_uint32 flag, const tjs_char *membername, tjs_uint32 *hint, const tTJSVariant *param, iTJSDispatch2 *objthis)
    {
        v[ttstr_to_pystr(membername)] = tjs_variant_to_py_object(*param);
        return TJS_S_OK;
    }

    public: tjs_error TJS_INTF_METHOD PropSetByNum(tjs_uint32 flag, tjs_int num, const tTJSVariant *param, iTJSDispatch2 *objthis)
    {
        v[py::int_(num)] = tjs_variant_to_py_object(*param);
        return TJS_S_OK;
    }

    public: tjs_error TJS_INTF_METHOD EnumMembers(tjs_uint32 flags, tTJSVariantClosure *callback, iTJSDispatch2 *objthis)
    {
        py::list property_names = v;
        size_t length = py::len(property_names);
        tTJSVariant name;
        tTJSVariant newflags = 0;
        tTJSVariant value;
        tTJSVariant * params[3] = { &name, &newflags, &value };
        for (size_t i = 0; i < length; i += 1)
        {
            name = py_object_to_tjs_variant(property_names[i]);
            if (!(flags & TJS_ENUM_NO_VALUE))
            {
                value = py_object_to_tjs_variant(v[property_names[i]]);
            }
            tTJSVariant res;
            callback->FuncCall( 0, NULL, NULL, &res, (flags & TJS_ENUM_NO_VALUE) ? 2 : 3, params, NULL);
        }
        return TJS_S_OK;
    }

    public: tjs_error TJS_INTF_METHOD DeleteMember(tjs_uint32 flag, const tjs_char *membername, tjs_uint32 *hint, iTJSDispatch2 *objthis)
    {
        v.attr("__delitem__")(v, membername);
        return TJS_S_OK;
    }

    public: tjs_error TJS_INTF_METHOD DeleteMemberByNum(tjs_uint32 flag, tjs_int num, iTJSDispatch2 *objthis)
    {
        v.attr("__delitem__")(v, num);
        return TJS_S_OK;
    }

    public: tjs_error TJS_INTF_METHOD IsInstanceOf(tjs_uint32 flag, const tjs_char * membername, tjs_uint32 *hint, const tjs_char * classname, iTJSDispatch2 *objthis)
    {
        if (membername == nullptr)
        {
            if (!TJS_strcmp(classname, TJS_W("__internal_TJS2PY_wrapper")))
            {
                return TJS_S_TRUE;
            }
        }
        return TJS_S_FALSE;
    }

    public: py::object get_object()
    {
        return v;
    }

    protected: py::object v = py::none();
};

static void translate_tjs_error(tjs_error hr)
{
    switch (hr)
    {
        case TJS_E_MEMBERNOTFOUND:
            throw py::key_error();
            break;
        case TJS_E_NOTIMPL:
            TJS_eTJSError(TJSNotImplemented);
            break;
        case TJS_E_INVALIDPARAM:
            TJS_eTJSError(TJSInvalidParam);
            break;
        case TJS_E_BADPARAMCOUNT:
            TJS_eTJSError(TJSBadParamCount);
            break;
        case TJS_E_INVALIDTYPE:
            throw py::type_error();
            break;
        case TJS_E_INVALIDOBJECT:
            TJS_eTJSError(TJSInvalidObject);
            break;
        case TJS_E_ACCESSDENYED:
            throw py::value_error();
            break;
        case TJS_E_NATIVECLASSCRASH:
            TJS_eTJSError(TJSNativeClassCrash);
            break;
        default:
            break;
    }
}



class tTJSDispatch2Wrapper
{
    iTJSDispatch2 *dispatch;
    iTJSDispatch2 *dispatch_this;
public:
    tTJSDispatch2Wrapper(iTJSDispatch2 *in_dispatch, iTJSDispatch2 *in_dispatch_this=NULL)
    {
        dispatch = in_dispatch;
        dispatch_this = in_dispatch_this;
        if (dispatch)
        {
            dispatch->AddRef();
        }
        if (dispatch_this)
        {
            dispatch_this->AddRef();
        }
    }

    ~tTJSDispatch2Wrapper(void)
    {
        if (dispatch)
        {
            dispatch->Release();
        }
        if (dispatch_this)
        {
            dispatch_this->Release();
        }
    }

    iTJSDispatch2 *GetNoAddRef(void)
    {
        return dispatch;
    }

    iTJSDispatch2 *GetThisNoAddRef(void)
    {
        return dispatch_this;
    }

    py::object PySpecialCall(py::args args)
    {
        tTJSVariant ret;
        size_t args_length = py::len(args);
        tTJSVariant params[args_length];
        tTJSVariant newflags = 0;
        tTJSVariant value;
        tTJSVariant * param_ptrs[args_length];
        for (size_t i = 0; i < args_length; i += 1)
        {
            param_ptrs[i] = &params[i];
            params[i] = py_object_to_tjs_variant(args[i]);
        }
        if (dispatch->IsInstanceOf(0, nullptr, nullptr, TJS_W("Class"), dispatch_this) == TJS_S_TRUE)
        {
            iTJSDispatch2 *dsp;
            tjs_error hr = dispatch->CreateNew(0, NULL, NULL, &dsp, args_length, param_ptrs, dispatch_this);
            translate_tjs_error(hr);
            return py::cast(new tTJSDispatch2Wrapper(dsp, dsp));
        }
        tjs_error hr = dispatch->FuncCall(0, NULL, NULL, &ret, args_length, param_ptrs, dispatch_this);
        translate_tjs_error(hr);
        return tjs_variant_to_py_object(ret);
    }

    py::str PySpecialStr(void)
    {
        ttstr result;
        result.printf(TJS_W("<tTJSDispatch2Wrapper 0x%p:0x%p>"), dispatch, dispatch_this);
        return ttstr_to_pystr(result);
    }

    py::bool_ PySpecialBool(void)
    {
        return !!dispatch;
    }

    py::object PySpecialLen(void)
    {
        tjs_int result;
        if (dispatch->IsInstanceOf(0, nullptr, nullptr, TJS_W("Array"), dispatch_this) == TJS_S_TRUE)
        {
            return py::int_(TJSGetArrayElementCount(dispatch));
        }
        tjs_error hr = dispatch->GetCount(&result, NULL, NULL, dispatch_this);
        translate_tjs_error(hr);
        return py::int_(result);
    }

    py::list ToPyList(bool return_array_elements=true)
    {
        if (return_array_elements && dispatch->IsInstanceOf(0, nullptr, nullptr, TJS_W("Array"), dispatch_this) == TJS_S_TRUE)
        {
            py::list list;
            tjs_int count = TJSGetArrayElementCount(dispatch);
            for (tjs_int i = 0; i < count; i += 1)
            {
                tTJSVariant item;
                dispatch->PropGetByNum(0, i, &item, dispatch_this);
                list.append(tjs_variant_to_py_object(item));
            }
            return list;
        }

        class tCallback : public tTJSDispatch
        {
        public:
            py::list list;
            tjs_error TJS_INTF_METHOD FuncCall(
                tjs_uint32 flag, const tjs_char * membername, tjs_uint32 *hint,
                tTJSVariant *result, tjs_int numparams, tTJSVariant **param,
                iTJSDispatch2 *objthis)
            {
                list.append(tjs_variant_to_py_object(*param[0]));
                if(result) *result = (tjs_int)(1);
                return TJS_S_OK;
            }
        };

        tCallback callback;

        tTJSVariantClosure clo(&callback, (iTJSDispatch2*)NULL);
        dispatch->EnumMembers(TJS_ENUM_NO_VALUE, &clo, dispatch_this);
        return callback.list;
    }

    py::object PySpecialDir(void)
    {
        return ToPyList(false);
    }

    py::object PySpecialIter(void)
    {
        return ToPyList().attr("__iter__")();
    }

    py::object PySpecialGetItem(py::object key)
    {
        tTJSVariant ret;
        if (py::isinstance<py::int_>(key))
        {
            tjs_error hr = dispatch->PropGetByNum(TJS_MEMBERMUSTEXIST, key.cast<tjs_int>(), &ret, dispatch_this);
            // Throw index error instead of key error for integer
            if (hr == TJS_E_MEMBERNOTFOUND)
            {
                throw py::index_error();
            }
            translate_tjs_error(hr);
        }
        else
        {
            tjs_error hr = dispatch->PropGet(TJS_MEMBERMUSTEXIST, key.cast<tjs_string>().c_str(), NULL, &ret, dispatch_this);
            translate_tjs_error(hr);
        }
        return tjs_variant_to_py_object(ret);
    }

    void PySpecialSetItem(py::object key, py::object value)
    {
        tTJSVariant param = py_object_to_tjs_variant(value);
        if (py::isinstance<py::int_>(key))
        {
            tjs_error hr = dispatch->PropSetByNum(TJS_MEMBERENSURE, key.cast<tjs_int>(), &param, dispatch_this);
            // Throw index error instead of key error for integer
            if (hr == TJS_E_MEMBERNOTFOUND)
            {
                throw py::index_error();
            }
            translate_tjs_error(hr);
        }
        else
        {
            tjs_error hr = dispatch->PropSet(TJS_MEMBERENSURE, key.cast<tjs_string>().c_str(), NULL, &param, dispatch_this);
            translate_tjs_error(hr);
        }
    }

    void PySpecialDelItem(py::object v)
    {
        tTJSVariant param = py_object_to_tjs_variant(v);
        if (py::isinstance<py::int_>(v))
        {
            tjs_error hr = dispatch->DeleteMemberByNum(0, v.cast<tjs_int>(), dispatch_this);
            // Throw index error instead of key error for integer
            if (hr == TJS_E_MEMBERNOTFOUND)
            {
                throw py::index_error();
            }
            translate_tjs_error(hr);
        }
        else
        {
            tjs_error hr = dispatch->DeleteMember(0, v.cast<tjs_string>().c_str(), NULL, dispatch_this);
            translate_tjs_error(hr);
        }
    }
};

static tTJSVariant py_object_to_tjs_variant(py::object v)
{
    if (py::isinstance<py::int_>(v))
    {
        return v.cast<tTVInteger>();
    }
    else if (py::isinstance<py::bool_>(v))
    {
        return !!v.cast<tTVInteger>();
    }
    else if (py::isinstance<py::float_>(v))
    {
        return v.cast<tjs_real>();
    }
    else if (py::isinstance<py::str>(v))
    {
        return ttstr(v.cast<tjs_string>());
    }
    else if (py::isinstance<py::bytes>(v))
    {
        std::string str = v.cast<std::string>();
        return tTJSVariant((tjs_uint8 *)str.data(), str.size());
    }
    else if (py::isinstance<tTJSDispatch2Wrapper>(v))
    {
        return tTJSVariant(v.cast<tTJSDispatch2Wrapper *>()->GetNoAddRef(), v.cast<tTJSDispatch2Wrapper *>()->GetThisNoAddRef());
    }
    else if (py::isinstance<py::none>(v))
    {
        return tTJSVariant();
    }
    else
    {
        iTJSDispatch2 * dispatch = new iTJSDispatch2WrapperForPython(v);
        tTJSVariant var(dispatch, dispatch);
        dispatch->Release();
        return var;
    }
    return tTJSVariant();
}


static py::object tjs_variant_to_py_object(tTJSVariant v)
{
    tTJSVariantType type = v.Type();
    if (type == tvtInteger)
    {
        return py::cast(v.AsInteger());
    }
    else if (type == tvtReal)
    {
        return py::cast(v.AsReal());
    }
    else if (type == tvtString)
    {
        return py::cast(tTJSString(v).AsStdString());
    }
    else if (type == tvtOctet)
    {
        return py::bytes((const char *)v.AsOctetNoAddRef()->GetData(), v.AsOctetNoAddRef()->GetLength());
    }
    else if (type == tvtObject)
    {
        iTJSDispatch2 *obj = v.AsObjectNoAddRef();
        iTJSDispatch2 *objthis = v.AsObjectThisNoAddRef();
        if (obj == nullptr)
        {
            return py::none();
        }
        if (obj->IsInstanceOf(0, nullptr, nullptr, TJS_W("__internal_TJS2PY_wrapper"), nullptr) == TJS_S_TRUE)
        {
            iTJSDispatch2WrapperForPython *obj_wrap = (iTJSDispatch2WrapperForPython *)obj;
            py::object ret = obj_wrap->get_object();
            return ret;
        }
        return py::cast(new tTJSDispatch2Wrapper(obj, objthis));
    }
    return py::none();
}

class tTJSWrapper
{
    tTJS *ScriptEngine;
public:
    tTJSWrapper()
    {
        ScriptEngine = new tTJS();
    }

    ~tTJSWrapper()
    {
        ScriptEngine->Release();
    }

    tTJSDispatch2Wrapper* GetGlobal()
    {
        return new tTJSDispatch2Wrapper(ScriptEngine->GetGlobalNoAddRef(), ScriptEngine->GetGlobalNoAddRef());
    }

    py::object ExecScript(py::str script, py::object context, py::str name, py::int_ lineofs)
    {
        tTJSVariant ret;
        iTJSDispatch2 *context_dispatch = NULL;
        if (py::isinstance<tTJSDispatch2Wrapper>(context))
        {
            context_dispatch = context.cast<tTJSDispatch2Wrapper *>()->GetNoAddRef();
        }
        size_t name_len = py::len(name);
        ScriptEngine->ExecScript(script.cast<tjs_string>().c_str(), &ret, context_dispatch, name_len > 0 ? name.cast<tjs_string>().c_str() : NULL, lineofs.cast<tjs_int>());
        return tjs_variant_to_py_object(ret);
    }

    py::object EvalExpression(py::str script, py::object context, py::str name, py::int_ lineofs)
    {
        tTJSVariant ret;
        iTJSDispatch2 *context_dispatch = NULL;
        if (py::isinstance<tTJSDispatch2Wrapper>(context))
        {
            context_dispatch = context.cast<tTJSDispatch2Wrapper *>()->GetNoAddRef();
        }
        size_t name_len = py::len(name);
        ScriptEngine->EvalExpression(script.cast<tjs_string>().c_str(), &ret, context_dispatch, name_len > 0 ? name.cast<tjs_string>().c_str() : NULL, lineofs.cast<tjs_int>());
        return tjs_variant_to_py_object(ret);
    }

    void SetPPValue(const tjs_char *name, const tjs_int32 value)
    {
        ScriptEngine->SetPPValue(name, value);
    }

    tjs_int32 GetPPValue(const tjs_char *name)
    {
        return ScriptEngine->GetPPValue(name);
    }

    void DoGarbageCollection(void)
    {
        ScriptEngine->DoGarbageCollection();
    }

    py::object LoadByteCode(py::bytes buff, py::object context, py::str name)
    {
        tTJSVariant ret;
        iTJSDispatch2 *context_dispatch = NULL;
        if (py::isinstance<tTJSDispatch2Wrapper>(context))
        {
            context_dispatch = context.cast<tTJSDispatch2Wrapper *>()->GetNoAddRef();
        }
        std::string str = buff.cast<std::string>();
        size_t name_len = py::len(name);
        ScriptEngine->LoadByteCode((const tjs_uint8 *)str.data(), str.size(), &ret, context_dispatch, name_len > 0 ? name.cast<tjs_string>().c_str() : NULL);
        return tjs_variant_to_py_object(ret);
    }

    py::bytes CompileScript(py::str script, py::bool_ isresultneeded, py::bool_ outputdebug, py::bool_ isexpression, py::str name, py::int_ lineofs)
    {
        size_t name_len = py::len(name);
        tTVPMemoryStream *outputstream = new tTVPMemoryStream;
        try 
        {
            ScriptEngine->CompileScript(script.cast<tjs_string>().c_str(), outputstream, !!isresultneeded, !!outputdebug, !!isexpression, name_len > 0 ? name.cast<tjs_string>().c_str() : NULL, lineofs);
        }
        catch (...) 
        {
            outputstream->Destruct();
            throw;
        }
        outputstream->Seek( 0, TJS_BS_SEEK_SET );
        tjs_uint64 streamlen = outputstream->GetSize();
        tjs_uint8 buff[static_cast<unsigned int>(streamlen)];
        outputstream->Read( buff, static_cast<tjs_uint>(streamlen) );
        outputstream->Destruct();
        return py::bytes((const char *)buff, (size_t)streamlen);
    }
};

PYBIND11_MODULE(pytjs, m) {
    py::class_<tTJSWrapper>(m, "tTJS")
        .def(py::init<>())
        .def("GetGlobal", &tTJSWrapper::GetGlobal, "Get the TJS2 global object")
        .def("ExecScript", &tTJSWrapper::ExecScript, "Executes a TJS2 script", py::arg("script"), py::arg("context") = py::none(), py::arg("name") = "",  py::arg("lineofs") = 0)
        .def("EvalExpression", &tTJSWrapper::EvalExpression, "Evaluates a TJS2 expression", py::arg("script"), py::arg("context") = py::none(), py::arg("name") = "",  py::arg("lineofs") = 0)
        .def("SetPPValue", &tTJSWrapper::SetPPValue, "Set a preprocessor value", py::arg("name"), py::arg("value"))
        .def("GetPPValue", &tTJSWrapper::GetPPValue, "Get a preprocessor value", py::arg("name"))
        .def("DoGarbageCollection", &tTJSWrapper::DoGarbageCollection, "Do garbage collection")
        .def("LoadByteCode", &tTJSWrapper::LoadByteCode, "Load a TJS2 bytecode", py::arg("buff"), py::arg("context") = py::none(), py::arg("name") = "")
        .def("CompileScript", &tTJSWrapper::CompileScript, "Compile a TJS2 script to bytecode", py::arg("script"), py::arg("isresultneeded") = false, py::arg("outputdebug") = false, py::arg("isexpression") = false, py::arg("name") = "", py::arg("lineofs") = 0)
        ;

    py::class_<tTJSDispatch2Wrapper>(m, "iTJSDispatch2")
        .def("__call__", &tTJSDispatch2Wrapper::PySpecialCall)
        .def("__str__", &tTJSDispatch2Wrapper::PySpecialStr)
        .def("__bool__", &tTJSDispatch2Wrapper::PySpecialBool)
        .def("__len__", &tTJSDispatch2Wrapper::PySpecialLen)
        .def("__dir__", &tTJSDispatch2Wrapper::PySpecialDir)
        .def("__iter__", &tTJSDispatch2Wrapper::PySpecialIter)
        .def("__getitem__", &tTJSDispatch2Wrapper::PySpecialGetItem)
        .def("__getattr__", &tTJSDispatch2Wrapper::PySpecialGetItem)
        .def("__setitem__", &tTJSDispatch2Wrapper::PySpecialSetItem)
        .def("__setattr__", &tTJSDispatch2Wrapper::PySpecialSetItem)
        .def("__delitem__", &tTJSDispatch2Wrapper::PySpecialDelItem)
        .def("__delattr__", &tTJSDispatch2Wrapper::PySpecialDelItem)
        ;
    py::register_exception_translator([](std::exception_ptr p) {
        try
        {
            if (p) std::rethrow_exception(p);
        }
        catch (const eTJSScriptException &e)
        {
            PyErr_SetString(PyExc_RuntimeError, std::string(py::str(py::cast(e.GetMessage().AsStdString()))).c_str());
        }
        catch (const eTJSScriptError &e)
        {
            PyErr_SetString(PyExc_RuntimeError, std::string(py::str(py::cast(e.GetMessage().AsStdString()))).c_str());
        }
        catch (const eTJSError &e)
        {
            PyErr_SetString(PyExc_RuntimeError, std::string(py::str(py::cast(e.GetMessage().AsStdString()))).c_str());
        }
        catch (const eTJS &e)
        {
            PyErr_SetString(PyExc_RuntimeError, std::string(py::str(py::cast(e.GetMessage().AsStdString()))).c_str());
        }
    });


#ifdef VERSION_INFO
    m.attr("__version__") = MACRO_STRINGIFY(VERSION_INFO);
#else
    m.attr("__version__") = "dev";
#endif
}
