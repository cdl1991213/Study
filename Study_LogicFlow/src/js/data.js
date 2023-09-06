export const lfData = {
    nodes: [
        {
            id: "node_id_1",
            type: "rect",
            x: 100,
            y: 100,
            text: "矩形"
        },

        {
            id: "node_id_2",
            type: "circle",
            x: 300,
            y: 100,
            text: "圆形"
        },

        {
            id: "node_id_3",
            type: "ellipse",
            x: 500,
            y: 100,
            text: "椭圆"
        },

        {
            id: "node_id_4",
            type: "polygon",
            x: 100,
            y: 250,
            text: "多边形"
        },

        {
            id: "node_id_5",
            type: "diamond",
            x: 500,
            y: 400,
            text: "菱形"
        },

        {
            id: "node_id_6",
            type: "text",
            x: 300,
            y: 400,
            text: "纯文本节点"
        },

        {
            id: "node_id_7",
            type: "html",
            x: 100,
            y: 400,
            text: "html节点"
        }
    ],
    
    edges: [
        {
            id: "edge_id_1",
            type: "line",
            sourceNodeId: "node_id_1",
            targetNodeId: "node_id_2",
            text: { x: 200, y: 100, value: "line连线" },
            startPoint: { x: 100, y: 100 },
            endPoint: { x: 300, y: 100 },
            pointsList: [],
            properties: {},
        },
        {
            id: "edge_id_2",
            type: "polyline",
            sourceNodeId: "node_id_3",
            targetNodeId: "node_id_4",
            text: { x: 300, y: 200, value: "polyline连线" },
            startPoint: { x: 500, y: 100 },
            endPoint: { x: 100, y: 250 },
            pointsList: [
                { x: 500, y: 100 },
                { x: 500, y: 200 },
                { x: 100, y: 200 },
                { x: 100, y: 250 },
            ],
            properties: {},
        },
        {
            id: "edge_id_3",
            type: "bezier",
            sourceNodeId: "node_id_5",
            targetNodeId: "node_id_7",
            text: { x: 300, y: 300, value: "bezier连线" },
            startPoint: { x: 500, y: 400 },
            endPoint: { x: 100, y: 400 },
            pointsList: [
                { x: 500, y: 400 },
                { x: 500, y: 300 },
                { x: 100, y: 300 },
                { x: 100, y: 400 },
            ],
            properties: {},
        },
    ],
};

export const obmTemplate1Data = {
    nodes: [
        {
            id: "node_id_1",
            type: "rect",
            x: 200,
            y: 100,
            text: "template-1-node-1"
        },
        {
            id: "node_id_2",
            type: "rect",
            x: 200,
            y: 200,
            text: "template-1-node-2"
        },
        {
            id: "node_id_3",
            type: "rect",
            x: 200,
            y: 300,
            text: "template-1-node-3"
        },
        {
            id: "node_id_4",
            type: "rect",
            x: 200,
            y: 400,
            text: "template-1-node-4"
        },
        

    ],
    
    edges: [
        {
            id: "edge_id_1",
            type: "line",
            sourceNodeId: "node_id_1",
            targetNodeId: "node_id_2",
            // text: { x: 150, y: 200, value: "line" },
            startPoint: { x: 200, y: 100 },
            endPoint: { x: 200, y: 200 },
            pointsList: [],
            properties: {},
        },
        {
            id: "edge_id_2",
            type: "line",
            sourceNodeId: "node_id_2",
            targetNodeId: "node_id_3",
            // text: { x: 150, y: 200, value: "line" },
            startPoint: { x: 200, y: 200 },
            endPoint: { x: 200, y: 300 },
            pointsList: [],
            properties: {},
        },
        {
            id: "edge_id_3",
            type: "line",
            sourceNodeId: "node_id_3",
            targetNodeId: "node_id_4",
            // text: { x: 150, y: 200, value: "line" },
            startPoint: { x: 200, y: 300 },
            endPoint: { x: 200, y: 400 },
            pointsList: [],
            properties: {},
        },
    ],
};

export const obmTemplate2Data = {
    nodes: [
        {
            id: "node_id_1",
            type: "rect",
            x: 400,
            y: 100,
            text: "template-2-node-1"
        },
        {
            id: "node_id_2",
            type: "rect",
            x: 400,
            y: 200,
            text: "template-2-node-2"
        },
        {
            id: "node_id_3",
            type: "rect",
            x: 400,
            y: 300,
            text: "template-2-node-3"
        },
        {
            id: "node_id_4",
            type: "rect",
            x: 400,
            y: 400,
            text: "template-2-node-4"
        },
        

    ],
    
    edges: [
        {
            id: "edge_id_1",
            type: "line",
            sourceNodeId: "node_id_1",
            targetNodeId: "node_id_2",
            // text: { x: 150, y: 200, value: "line" },
            startPoint: { x: 400, y: 100 },
            endPoint: { x: 400, y: 200 },
            pointsList: [],
            properties: {},
        },
        {
            id: "edge_id_2",
            type: "line",
            sourceNodeId: "node_id_2",
            targetNodeId: "node_id_3",
            // text: { x: 150, y: 200, value: "line" },
            startPoint: { x: 400, y: 200 },
            endPoint: { x: 400, y: 300 },
            pointsList: [],
            properties: {},
        },
        {
            id: "edge_id_3",
            type: "line",
            sourceNodeId: "node_id_3",
            targetNodeId: "node_id_4",
            // text: { x: 150, y: 200, value: "line" },
            startPoint: { x: 400, y: 300 },
            endPoint: { x: 400, y: 400 },
            pointsList: [],
            properties: {},
        },
    ],
};

