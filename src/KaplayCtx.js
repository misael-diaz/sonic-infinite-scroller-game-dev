import kaplay from "kaplay";
const k = kaplay({
	width: 1920,
	height: 1080,
	letterbox: true,
	background: [0, 0, 0],
	buttons: {
		jump: {
			keyboard: ["space"],
			mouse: "left",
		},
	},
	debugKey: "d",
	debug: true,
	touchToMouse: true,
	global: false,
});
export default k;
/*

Kaplay Context
so that we can call kaplay's functions via k.foo() ... a way to avoid name collisions

*/
