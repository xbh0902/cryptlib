package me.xbh.lib.core.cxx

/**
* <p>
* 描述：MD5本地接口
* </p>
* 创建日期：2017年11月02日.
* @author wenbin.zhou@ehking.com
* @version 1.0
*/

internal class Md5 constructor(){
    external fun digest(plainText: String): String
}
