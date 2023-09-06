<template>
    <div class="context-menu" :style="{ left: x + 'px', top: y + 'px' }">
        <ul>
            <li @click="handleOptionClick('Option 1')">新增节点</li>
            <li @click="handleOptionClick('Option 2')">删除节点</li>
            <!-- Add more options as needed -->
        </ul>
    </div>
</template>
  
  <script>
export default {
    name:"ContextMenu",
    props: {
        x: Number,
        y: Number,
    },
    methods: {
        handleOptionClick(option) {
            this.$emit("optionClick", option);
        },
    },
};
</script>
  
  <style>
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
  