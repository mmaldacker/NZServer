<div class="footer">
  <div class="container clear">
    <div class="left col-6 text-left">
      Built by Maximilian Maldacker
    </div>
    <div class="right col-6">
      <ul class="list-inline footer-list">
      <li><a href="/login">login</a></li>
      {% if string.match(uri, "edit$") then %}
      {{[[<li><a href="]].. uri ..[[">edit</a></li>]]}}
      {% else %}
      {{[[<li><a href="]].. uri ..[[/edit">edit</a></li>]]}}
      {% end %}
      </ul>
    </div>
  </div>
</div>