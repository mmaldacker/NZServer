<!DOCTYPE html>
<html lang="en" class="no-js">
{# head #}
<body>

{% header = {title = "Articles", abstract = "Some informative texts and tutorials"} %}

{# header #}

{% a = articles.get(arguments[0]) %}

<div class="grey-row" id="headings">
  <div class="container row-2 font-light">
    <div class="clear row">
{% if arguments[1] == "edit" then %}
		<form action="" method="post">
		  <fieldset>
		    <legend>Edit</legend>

		      <label for="title">Title</label>
		      <input type="text" name="title" cols="60" value="{{a:title()}}">

     		 <label for="content">Content</label>
   		     <textarea name="content" cols="80" rows="20">{{a:content()}}</textarea>

		      <input type="submit" value="Edit" class="button">
		  </fieldset>
		</form>
{% else %}
      <h2 class="h3 font-light">{{a:title()}}</h2>
      <p>{{a:content()}}</p>
{% end %}
    </div>
  </div>
</div>

<div class="footer">
  <div class="container clear">
    <div class="left col-6 text-left">
      Built by Maximilian Maldacker
    </div>
    <div class="right col-6">
      <ul class="list-inline footer-list">
      <li><a href="/login">login</a></li>
      <li><a href="/edit">edit</a></li>
      </ul>
    </div>
  </div>
</div>

<script src="/file/js/default.js"></script>

</body>
</html>
