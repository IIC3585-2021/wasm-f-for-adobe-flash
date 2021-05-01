function createGraph(data) {
  // create a chart from the loaded data
  const chart = anychart.graph();

  // set the title
  chart.title("Grafo entregado");

  // draw the chart
  chart.container("graph-div").draw();

  return chart;
}

function reDraw(chart, json) {
  const newChart = anychart.graph();

  // set the title
  newChart.title("Grafo entregado");
  newChart.data(json);

  chart.container("graph-div").remove();
  const parent = document.getElementById("graph-div")
  while (parent.firstChild) {
    parent.removeChild(parent.firstChild);
  }
  newChart.container("graph-div").draw()

  const nodes = newChart.nodes();
  const edges = newChart.edges();

  // set the size of nodes
  nodes.normal().height(30);
  nodes.hovered().height(45);
  nodes.selected().height(45);

  // set the stroke of nodes
  nodes.normal().stroke(null);
  nodes.hovered().stroke("#333333", 3);
  nodes.selected().stroke("#333333", 3);

  // enable the labels of nodes
  newChart.nodes().labels().enabled(true);

  // configure the labels of nodes
  newChart.nodes().labels().format("{%id}");
  newChart.nodes().labels().fontSize(12);
  newChart.nodes().labels().fontWeight(600);

  newChart.edges().labels().enabled(true)


  newChart.edges().labels().format("{%weight}")
  newChart.edges().labels().fontSize(12);
  newChart.edges().labels().fontWeight(600);
  newChart.edges().tooltip().format("from: {%from}\nto: {%to}\nweight: {%weight}")
  return newChart
}

export {createGraph, reDraw};