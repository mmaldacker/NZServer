<!DOCTYPE html>
<html lang="en" class="no-js">
{# head #}
<body>

{% header = {title = "Articles", abstract = "Some informative texts and tutorials"} %}

{# header #}

{% a = article.get_for(arguments[0]) %}

<div class="grey-row" id="headings">
  <div class="container row-2 font-light">
    <div class="clear row">
{% if arguments[1] == "edit" and headers["Cookie"] and session.is_logged_in(headers["Cookie"]) then %}
{{[[
		<form action="" method="post">
		  <fieldset>
		    <legend>Edit</legend>

		      <label for="title">Title</label>
		      <input type="text" name="title" cols="60" value="]]}} {{a.title}} {{[[">

     		 <label for="content">Content</label>
   		     <textarea name="content" cols="80" rows="20">]]}} {{a.content}} {{[[</textarea>

		      <input type="submit" value="Edit" class="button">
		  </fieldset>
		</form>
]]}}
{% else %}
{{[[
      <h2 class="h3 font-light">]]}} {{a.title}} {{[[</h2>
      <p>]]}} {{a.content}} {{[[</p>
]]}}
{% end %}
    </div>
  </div>
</div>

{# footer #}

<script src="/file/js/default.js"></script>

</body>
</html>
