<template>
    <div class="all">
        <div class="top">
            <div class="left">
                <FlowChart ref="flowchart" :key="childComponentKey" />
            </div>
            <div class="right">
                <div>节点基础信息配置</div>
                <div>
                    <button @click="subBusinessProcessData">保存</button>
                    <button @click="resetBusinessProcessData">重置</button>
                </div>
            </div>
        </div>
        <div>
            <button>配置节点属性</button>
        </div>
    </div>
</template>
  
<script>
import FlowChart from "@/components/FlowChart";

export default {
    name: "BusinessProcessConfiguration",
    components: {
        FlowChart,
    },
    data() {
        return {
            initialBusinessProcessData: {},
            childComponentKey: 1,
        };
    },
    mounted() {
        // 保存初始业务流程数据
        this.initialBusinessProcessData =
            this.$refs.flowchart.currentBusinessProcessData;
    },
    methods: {
        subBusinessProcessData() {
            this.initialBusinessProcessData =
            this.$refs.flowchart.currentBusinessProcessData;
            // 提交数据
            console.log(this.initialBusinessProcessData);
        },
        resetBusinessProcessData() {
            this.childComponentKey += 1;
        },
    },
};
</script>
  
  <style scoped>
.all {
    margin-left: 10%;
    margin-right: 10%;
    width: 80%;
    height: 80%;
}
.top{
    width: 100%;
    height: 98%;
}
.left {
    width: 40%;
    height: 100%;
    border: 1px solid black;
    float: left;
}
.right {
    width: 40%;
    height: 100%;
    border: 1px solid red;
    float: right;
}
</style>