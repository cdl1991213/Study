// api接口统一管理
import requests_mock from "./requestsMock";

/* 流程模板 */
export const reqBusinessProcessTemplate1 = (params) => {
  // 发送请求，返回promise对象
  return requests_mock({
    url: "/businessProcessTemplate1",
    method: "post",
    data:params
  });
};

/* 流程模板 */
export const reqBusinessProcessTemplate2 = (params) => {
    // 发送请求，返回promise对象
    return requests_mock({
      url: "/businessProcessTemplate2",
      method: "post",
      data:params
    });
  };

