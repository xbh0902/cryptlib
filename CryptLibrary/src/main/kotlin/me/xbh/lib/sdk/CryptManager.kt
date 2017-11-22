package me.xbh.lib.sdk

import me.xbh.lib.core.CryptService
import me.xbh.lib.core.cxx.CryptServiceImpl
import me.xbh.lib.core.java.CryptServiceJavaImpl

/**
 * <p>
 * 描述： 提供加密工具
 * </p>
 * 创建日期：2017年11月22日.
 * @author wenbin.zhou@ehking.com
 * @version 1.0
 */
object CryptManager {

    init {
        //System.loadLibrary("supportjni")
        System.loadLibrary("crypt1")
    }

    /**
     * c++实现
     */
    fun getDefault() = CryptProxy(CryptServiceImpl()).getProxy<CryptService>()

    /**
     * java实现
     */
    fun getStandard() = CryptProxy(CryptServiceJavaImpl()).getProxy<CryptService>()
}