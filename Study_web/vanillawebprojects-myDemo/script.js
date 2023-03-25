const rulesBtn = document.getElementById('rules-btn');
const closeBtn = document.getElementById('close-btn');
const rules = document.getElementById('rules');
const canvas = document.getElementById('canvas');
const ctx = canvas.getContext('2d');

let score = 0;

// 每行砖块
const brickRowCount = 9;
// 每列砖块
const brickColumnCount = 5;

const delay = 500; 

// 准备对象
// 1. 球
const ball = {
    x: canvas.width / 2,    //圆心x坐标
    y: canvas.height / 2,   //圆心y坐标
    size: 10,   //半径
    speed: 4,   //球速
    dx: 4,      //x轴移动
    dy: -4,     //y轴移动
    visible: true
};
// 2. 球拍
const paddle = {
    x: canvas.width / 2 - 40,
    y: canvas.height - 20,
    w: 80,
    h: 10,
    speed: 8,
    dx: 0,
    visible: true
};
// 3. 砖块
const brickInfo = {
  w: 70,
  h: 20,
  padding: 10,
  offsetX: 45,  // 砖块的左侧留白
  offsetY: 60,  // 砖块的顶部留白
  visible: true
};
const bricks = [];
for(let i = 0; i < brickRowCount; i++){
    bricks[i] = [];
    for(let j = 0; j < brickColumnCount; j++){
        const x = i * (brickInfo.w + brickInfo.padding) + brickInfo.offsetX;
        const y = j * (brickInfo.h + brickInfo.padding) + brickInfo.offsetY;
        // ...扩展运算符,将对象/数组展开
        bricks[i][j] = {x, y, ...brickInfo};
    }
}

// 创建对象
// 1. 在画布中创建球
function drawBall() {
    ctx.beginPath();
    // 创建弧线/曲线
    // (圆心x坐标，圆心y坐标，圆半径，弧起始角，弧结束角，顺逆时针)
    ctx.arc(ball.x, ball.y, ball.size, 0, Math.PI * 2);
    //填充颜色
    ctx.fillStyle = ball.visible ? '#0095dd' : 'transparent';
    // 显示弧
    // stroke()描边，fill()填充
    ctx.fill();
    ctx.closePath();
}

// 2. 在画布中创建球拍
function drawPaddle() {
    ctx.beginPath();
    // 创建矩形
    // (矩形左上角x坐标，矩形左上角y坐标，宽度，高度)
    ctx.rect(paddle.x, paddle.y, paddle.w, paddle.h);
    ctx.fillStyle = paddle.visible ? '#0095dd' : 'transparent';
    ctx.fill();
    ctx.closePath();
}

// 3. 在画布中创建砖块
function drawBricks() {
    // 调用数组中每个元素
    // 箭头函数
    bricks.forEach(column => {  
      column.forEach(brick => {
        ctx.beginPath();
        ctx.rect(brick.x, brick.y, brick.w, brick.h);
        ctx.fillStyle = brick.visible ? '#0095dd' : 'transparent';
        ctx.fill();
        ctx.closePath();
      });
    });
}

// 4. 在画布中创建分数
function drawScore() {
    ctx.font = '20px Arial';
    // 在指定位置绘画文本
    ctx.fillText(`Score: ${score}`, canvas.width - 100, 30);
}

// 移动对象
// 1. 移动球
function moveBall() {
    ball.x += ball.dx;
    ball.y += ball.dy;
    

    // 对象交互
    // 墙边界（左右侧）
    if (ball.x + ball.size > canvas.width || ball.x - ball.size < 0) {
      ball.dx *= -1; // ball.dx = ball.dx * -1
    }
  
    // 墙边界（顶部）
    if (ball.y + ball.size > canvas.height || ball.y - ball.size < 0) {
      ball.dy *= -1;
    }
  
    // console.log(ball.x, ball.y);
  
    // 球拍边界
    if (
      ball.x - ball.size > paddle.x &&
      ball.x + ball.size < paddle.x + paddle.w &&
      ball.y + ball.size > paddle.y
    ) {
      ball.dy = -ball.speed;    
    }
  
    // 砖块边界
    bricks.forEach(column => {
      column.forEach(brick => {
        if (brick.visible) {
          if (
            ball.x + ball.size > brick.x && // left brick side check
            ball.x - ball.size < brick.x + brick.w && // right brick side check
            ball.y + ball.size > brick.y && // top brick side check
            ball.y - ball.size < brick.y + brick.h // bottom brick side check
          ) {
            ball.dy *= -1;
            brick.visible = false;
  
            increaseScore();
          }
        }
      });
    });
  
    // 墙边界（底部）——>失败
    if (ball.y + ball.size > canvas.height) {
      showAllBricks();
      score = 0;
    }
}

// 2. 移动球拍
function movePaddle() {
    paddle.x += paddle.dx;
  
    // Wall detection
    if (paddle.x + paddle.w > canvas.width) {
      paddle.x = canvas.width - paddle.w;
    }
  
    if (paddle.x < 0) {
      paddle.x = 0;
      }
}

// 加分
function increaseScore() {
    score++;
  
    if (score % (brickRowCount * brickColumnCount) === 0) {
  
        ball.visible = false;
        paddle.visible = false;
  
        //通关
        setTimeout(function () {
            showAllBricks();
            score = 0;
            paddle.x = canvas.width / 2 - 40;
            paddle.y = canvas.height - 20;
            ball.x = canvas.width / 2;
            ball.y = canvas.height / 2;
            ball.visible = true;
            paddle.visible = true;
        },delay)
    }
}

// 失败——>重置砖块
function showAllBricks() {
    bricks.forEach(column => {
      column.forEach(brick => (brick.visible = true));
    });
}

// 绘制画布
function draw(){
    // 清空指定区域
    ctx.clearRect(0, 0, canvas.width, canvas.height);

    drawBall();
    drawPaddle();
    drawBricks();
    drawScore();
}

// 实时更新画布
function update(){
    moveBall();
    movePaddle();
    
    draw();

    requestAnimationFrame(update);
}

// 键盘控制
// e为事件对象
// Keydown 
function keyDown(e) {
    if (e.key === 'Right' || e.key === 'ArrowRight') {
      paddle.dx = paddle.speed;
    } else if (e.key === 'Left' || e.key === 'ArrowLeft') {
      paddle.dx = -paddle.speed;
    }
  }
  
  // Keyup event
function keyUp(e) {
    if (
      e.key === 'Right' ||
      e.key === 'ArrowRight' ||
      e.key === 'Left' ||
      e.key === 'ArrowLeft'
    ) {
      paddle.dx = 0;
    }
}
  
// Keyboard event handlers
document.addEventListener('keydown', keyDown);
document.addEventListener('keyup', keyUp);

// rule块显示/隐藏
// 当指定的click事件发生时，触发函数
rulesBtn.addEventListener('click', () => rules.classList.add('show'));
closeBtn.addEventListener('click', () => rules.classList.remove('show'));


function main(){
    update();
}
main();



let p1 = new Promise((resolve, reject) => {
    setTimeout(() => {
        resolve('success')
    }, 1000)
});

let p2 = new Promise((resolve, reject) => {
    setTimeout(() => {
        reject('failed')
    }, 500)
});

Promise.race([p1, p2]).then((result) => {
    console.log(result);
}).catch((err) => {
    console.log(err);
})



