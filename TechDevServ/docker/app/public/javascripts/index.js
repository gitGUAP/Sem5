const $list = $(".g-list");

function getCard(data) {
  return `
<div class="card">
  <div class="g-index_img" style="background-image:url('${data.img}');"></div>
  <div class="card-body">
    <h5 class="card-title">${data.name}</h5>
    <p class="card-text">${data.desc}</p>
    <!-- <a href="#" class="btn btn-primary">Go somewhere</a> -->
  </div>
</div>`;
}

$.getJSON("/api/records", function(data) {
  for (const el of data) {
    $list.append(getCard(el));
  }
});
