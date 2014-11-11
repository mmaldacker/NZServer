<!DOCTYPE html>
<html lang="en" class="no-js">
{# head #}
<body>

{% header = {title = "Articles", abstract = "Some informative texts and tutorials"} %}

{# header #}

{% a = articles.get(article_name) %}

<div class="grey-row" id="headings">
  <div class="container row-2 font-light">
    <div class="clear row">
      <h2 class="h3 font-light">{{a:title()}}</h2>
      <p>{{a:content()}}</p>
    </div>
  </div>
</div>

<script src="/file/js/default.js"></script>

</body>
</html>
