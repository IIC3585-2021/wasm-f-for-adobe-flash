// function loadGraph(file) {
//   console.log(file)
//   anychart.data.loadJsonFile(file, function (data) {

//     // create a chart from the loaded data
//     var chart = anychart.graph(data);

//     // set the title
//     chart.title("Grafo entregado");

//     // access nodes
//     var nodes = chart.nodes();

//     // set the size of nodes
//     nodes.normal().height(30);
//     nodes.hovered().height(45);
//     nodes.selected().height(45);

//     // set the stroke of nodes
//     nodes.normal().stroke(null);
//     nodes.hovered().stroke("#333333", 3);
//     nodes.selected().stroke("#333333", 3);

//     // enable the labels of nodes
//     chart.nodes().labels().enabled(true);

//     // configure the labels of nodes
//     chart.nodes().labels().format("{%id}");
//     chart.nodes().labels().fontSize(12);
//     chart.nodes().labels().fontWeight(600);

//     // draw the chart
//     chart.container("graph-div").draw();

//   });
// };

function loadGraph(data) {
  // create a chart from the loaded data
  var chart = anychart.graph(data);

  // set the title
  chart.title("Grafo entregado");

  // access nodes
  var nodes = chart.nodes();

  // set the size of nodes
  nodes.normal().height(30);
  nodes.hovered().height(45);
  nodes.selected().height(45);

  // set the stroke of nodes
  nodes.normal().stroke(null);
  nodes.hovered().stroke("#333333", 3);
  nodes.selected().stroke("#333333", 3);

  // enable the labels of nodes
  chart.nodes().labels().enabled(true);

  // configure the labels of nodes
  chart.nodes().labels().format("{%id}");
  chart.nodes().labels().fontSize(12);
  chart.nodes().labels().fontWeight(600);

  // draw the chart
  chart.container("graph-div").draw();

  chart.edges().labels().enabled(true)


  chart.edges().labels().format("{%weight}")
  chart.edges().labels().fontSize(12);
  chart.edges().labels().fontWeight(600);
  chart.edges().tooltip().format("from: {%from}\nto: {%to}\nweight: {%weight}")

}

export {loadGraph};