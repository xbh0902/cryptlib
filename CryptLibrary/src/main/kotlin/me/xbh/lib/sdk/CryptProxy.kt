package me.xbh.lib.sdk

import android.util.Log
import java.lang.reflect.InvocationHandler
import java.lang.reflect.InvocationTargetException
import java.lang.reflect.Method
import java.lang.reflect.Proxy


@Suppress("UNCHECKED_CAST")
/**
 * <p>
 * 描述：这是一个代理
 * </p>
 * 创建日期：2017年11月21日.
 * @author wenbin.zhou@ehking.com
 * @version 1.0
 */
class CryptProxy(val target: Any) : InvocationHandler {

    private val TAG = "CryptProxy"


    override fun invoke(proxy: Any?, method: Method?, args: Array<out Any>): Any {
        var result: Any? = null
        try {
            var mlog = "Method -->${method?.name}("
            args.forEach {
                mlog += "arg${args.indexOf(it)}:$it${if (args.indexOf(it) == args.lastIndex) {
                    ""
                } else {
                    ", "
                }}"
            }
            mlog += ")"
            Log.d(TAG, mlog)

            result = method!!.invoke(target, *args)
        } catch (e: IllegalAccessException) {
            e.printStackTrace()
        } catch (e: InvocationTargetException) {
            val throwable = e.targetException
            Log.e(TAG, "Exception in :${method?.name}, message:${throwable.message}")
        }catch (e: Exception){
            e.printStackTrace()
        }
        return result!!
    }

    fun <T> getProxy(): T {
        return Proxy.newProxyInstance(
                target::class.java.classLoader,
                target::class.java.interfaces,
                this) as T
    }
}