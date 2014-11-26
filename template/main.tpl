<!DOCTYPE html>
<html lang="en" class="no-js">
{# head #}
<body>
{% header = {title = "Main", abstract = "Some informative texts and tutorials"} %}
{# header #}

<div class="grey-row" id="headings">
  <div class="container row-2 font-light">
    <div class="clear row">
{% 
for a in article.get_all() do
%}
{{[[
  <div class="col col-3">
    <a href="/articles/]].. a.short_title ..[[">]].. a.title ..[[</a>
    <img src="]].. a.image ..[[">
  </div>
]]}}
{%
end
%}
    </div>
  </div>
</div>

{# footer #}

<script src="/file/js/default.js"></script>

</body>
</html>
