/* 二次封装axios */
import axios from 'axios';
import nprogress from 'nprogress';
import "nprogress/nprogress.css"

const requests = axios.create({
    baseURL:"/api",  // 基础路径前缀
    timeout:5000,   //请求超时时间
})
// 增加请求拦截器：在发出请求之前进行操作
requests.interceptors.request.use((config) => {
    // 开启进度条
    nprogress.start()  
    
    return config
})
// 增加响应拦截器
requests.interceptors.response.use((res) => {
    // 请求成功的回调函数
    // 关闭进度条
    nprogress.done()

    return res.data
},(error) => {
    // 请求失败的回调函数
    return Promise.reject(new Error('fail'))
})

export default requests;