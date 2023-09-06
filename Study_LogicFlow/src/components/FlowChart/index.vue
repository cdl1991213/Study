<template>
    <div class="flowchart-all">
        <div class="button-container">
            <button class="button" @click="addRectNode">添加矩形节点</button>
        </div>
        <div class="container" ref="container"></div>
        <ul
            v-if="isContextMenuVisible"
            class="context-menu"
            :style="{ left: contextMenuX + 'px', top: contextMenuY + 'px' }"
        >
            <li @click="handleOptionClick('addNode')">新增节点</li>
            <li @click="handleOptionClick('deleteNode')">删除节点</li>
            <!-- Add more options as needed -->
        </ul>
    </div>
</template>
  
<script>
import LogicFlow from "@logicflow/core";
import "@logicflow/core/dist/style/index.css";
import { v4 as uuidv4 } from "uuid";
import { mapState } from "vuex";
import { snaplineTheme } from "@/js/theme.js";

export default {
    name: "FlowChart",
    components: {},
    computed: {
        ...mapState({
            businessProcessTemplateData: (state) => {
                return state.businessprocessconfiguration
                    .businessProcessTemplateData;
            },
        }),
    },
    data() {
        return {
            // Origin Node Id
            originNodeId: 0,
            // New Node Id
            latestNodeId: 0,
            // 最底部的节点
            bottomNode: 0,
            // 当前业务流程数据
            currentBusinessProcessData: {},

            /* 右键选项列表 */
            isContextMenuVisible: false,
            contextMenuX: 0,
            contextMenuY: 0,
        };
    },
    mounted() {
        console.log("FlowChart挂载");
        /* 初始化流程模板 */
        this.lf = new LogicFlow({
            // 绑定容器对象
            container: this.$refs.container,
            // 背景：网格点
            // grid: true
            grid: {
                size: 20, // 设置网格大小
                visible: false, // 设置是否可见，若设置为false则不显示网格线但是仍然保留size栅格的效果
                type: "dot", // 设置网格类型，目前支持 dot 点状和 mesh 线状两种
                config: {
                    color: "#ababab", // 设置网格的颜色
                    thickness: 1, // 设置网格线的宽度
                },
            },
            // 对齐线
            snapline: true,
        });
        this.lf.render(this.businessProcessTemplateData);
        this.lf.setTheme(snaplineTheme);

        /* 保存流程模板数据 */
        this.currentBusinessProcessData.nodes = this.lf.graphModel.nodes;
        this.currentBusinessProcessData.edges = this.lf.graphModel.edges;

        /* 获取底部节点 */
        // 遍历所有节点
        if (this.lf.graphModel.nodes.length == 0) {
            // pass
        } else {
            this.bottomNode = this.lf.graphModel.nodes[0];
            let bottomNodeY = this.lf.graphModel.nodes[0].y;
            this.lf.graphModel.nodes.forEach((node) => {
                if (bottomNodeY < node.y) {
                    bottomNodeY = node.y;
                    this.bottomNode = node;
                }
            });
        }

        /* 监听事件 */
        // 监听右键点击
        this.lf.on("node:contextmenu", (data) => {
            this.contextMenuX = data.e.clientX;
            this.contextMenuY = data.e.clientY;
            this.isContextMenuVisible = true;
        });
    },
    methods: {
        addRectNode() {
            // 判断1. 是否存在节点 2.是否已经新增过节点，若没有，找到底部节点；若有，使用最新节点
            if (this.bottomNode == 0) {
                // New Node Id
                this.latestNodeId = uuidv4();
                // New Node Data
                const newNodeConfig = {
                    id: this.latestNodeId,
                    type: "rect",
                    x: 100,
                    y: 100,
                    text: "New Rect Node",
                };
                this.lf.addNode(newNodeConfig);
                this.bottomNode = this.lf.graphModel.getNodeModelById(
                    this.latestNodeId
                );
                return;
            } else if (this.latestNodeId == 0) {
                this.originNodeId = this.bottomNode.id;
            } else {
                this.originNodeId = this.latestNodeId;
            }

            /* 新增节点 */
            // 新增前的最新节点
            let originNode = this.lf.graphModel.getNodeModelById(
                this.originNodeId
            );
            // New Node Id
            this.latestNodeId = uuidv4();
            // New Node Data
            const newNodeConfig = {
                id: this.latestNodeId,
                type: "rect",
                x: originNode.x,
                y: originNode.y + 100,
                text: "New Rect Node",
            };
            this.lf.addNode(newNodeConfig);

            /* 新增边 */
            // New Edge Data
            const newEdgeConfig = {
                id: uuidv4(),
                type: "line",
                sourceNodeId: this.originNodeId,
                targetNodeId: this.latestNodeId,
            };
            this.lf.addEdge(newEdgeConfig);

            /* 保存流程模板数据 */
            this.currentBusinessProcessData.nodes = this.lf.graphModel.nodes;
            this.currentBusinessProcessData.edges = this.lf.graphModel.edges;
        },
        handleOptionClick(option) {
            console.log("Clicked:", option);
            switch (option) {
                case "addNode":
                    this.addFixRectNode();
                    break;
                case "deleteNode":
                    this.deleteFixRectNode();
                    break;
            }
            this.isContextMenuVisible = false;
        },
        // 选中后，在右键选项列表新增节点
        addFixRectNode() {
            // 当前选中节点
            let currentlySelectedNode =
                this.lf.getSelectElements(false).nodes[0];
            // 当前节点所有的下一级节点
            let allLowerLevelNodes = this.lf.getNodeOutgoingNode(
                currentlySelectedNode.id
            );
            // 插入新节点
            let newNodeId = uuidv4();
            const newNodeConfig = {
                id: newNodeId,
                type: "rect",
                x: currentlySelectedNode.x,
                y: currentlySelectedNode.y + 100,
                text: "New Rect Node",
            };
            this.lf.addNode(newNodeConfig);
            let newNode = this.lf.graphModel.getNodeModelById(newNodeId);
            // 删除起点为当前节点的边
            this.lf.deleteEdgeByNodeId({
                sourceNodeId: currentlySelectedNode.id,
                targetNodeId: allLowerLevelNodes[0].id,
            });
            // 创建新的边，连接新节点
            this.lf.addEdge({
                type: "line",
                sourceNodeId: currentlySelectedNode.id,
                targetNodeId: newNode.id,
            });
            this.lf.addEdge({
                type: "line",
                sourceNodeId: newNode.id,
                targetNodeId: allLowerLevelNodes[0].id,
            });

            while (allLowerLevelNodes.length >= 1) {
                // 所有的下一级节点向下移动
                this.lf.graphModel.moveNode(
                    allLowerLevelNodes[0].id,
                    0,
                    100,
                    false
                );
                allLowerLevelNodes = this.lf.getNodeOutgoingNode(
                    allLowerLevelNodes[0].id
                );
            }
            // console.log(allLowerLevelNodes.length)
        },
        // 选中后，在右键选项列表删除节点
        deleteFixRectNode() {
            // 当前选中节点
            let currentlySelectedNode =
                this.lf.getSelectElements(false).nodes[0];
            // 当前节点所有的下一级节点
            let allLowerLevelNodes = this.lf.getNodeOutgoingNode(
                currentlySelectedNode.id
            );
            // 当前节点所有的上一级节点
            let allUpperLevelNode = this.lf.getNodeIncomingNode(
                currentlySelectedNode.id
            );
            // 删除当前节点
            this.lf.graphModel.deleteNode(currentlySelectedNode.id);
            if (allUpperLevelNode.length > 0 && allLowerLevelNodes.length > 0) {
                // 创建新的边，连接新节点
                this.lf.addEdge({
                    sourceNodeId: allUpperLevelNode[0].id,
                    targetNodeId: allLowerLevelNodes[0].id,
                });
            }
            while (allLowerLevelNodes.length >= 1) {
                // 所有的下一级节点向下移动
                this.lf.graphModel.moveNode(
                    allLowerLevelNodes[0].id,
                    0,
                    -100,
                    false
                );
                allLowerLevelNodes = this.lf.getNodeOutgoingNode(
                    allLowerLevelNodes[0].id
                );
            }
        },
    },
};
</script>
  
  <style scoped>
.flowchart-all {
    width: 100%;
    height: 100%;
}
.container {
    width: 100%;
    height: 100%;
}

.button-container {
    display: flex;
    flex-direction: row;
    align-items: flex-start;
    padding-left: 20px; /* 为按钮添加左侧间距 */
}
.button {
    margin-bottom: 10px; /* 按钮之间添加垂直间距 */
}
.context-menu {
    position: fixed;
    background-color: white;
    border: 1px solid #ccc;
    box-shadow: 0px 2px 4px rgba(0, 0, 0, 0.2);
    z-index: 9999;
}

.context-menu ul {
    list-style: none;
    padding: 0;
    margin: 0;
}

.context-menu li {
    padding: 8px 16px;
    cursor: pointer;
    user-select: none;
}

.context-menu li:hover {
    background-color: #f0f0f0;
}
</style>