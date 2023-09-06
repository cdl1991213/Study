import Mock from 'mockjs'
import businessProcessTemplate1 from './businessProcessTemplate1.json';
import businessProcessTemplate2 from './businessProcessTemplate2.json';

/* 
 mock数据 
 参数1：请求地址
 参数2：请求数据
*/
// 流程图数据
Mock.mock("/mock/businessProcessTemplate1", 'post', {
    code:200, 
    message: 'POST请求模拟成功',
    data:businessProcessTemplate1
})

Mock.mock("/mock/businessProcessTemplate2", 'post', {
    code:200, 
    message: 'POST请求模拟成功',
    data:businessProcessTemplate2
})