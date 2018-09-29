function del(id) {
    $.ajax({
        url: `/edit/delete/${id}`,
        type: 'DELETE',
        success: function(result) {
            // window.location.replace("/edit")
        }
    });
}

