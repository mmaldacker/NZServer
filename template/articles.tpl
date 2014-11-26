<!DOCTYPE html>
<html lang="en" class="no-js">
{# head #}
<body>

{% header = {title = "Articles", abstract = "Some informative texts and tutorials"} %}

{# header #}

{% 
if method == "POST" then
	local u = article()
	u.short_title = arguments[0]
	u.title = post["title"]
	u.abstract = post["abstract"]
	u.image = post["image"]
	u.content = post["content"]
	article.update(u)
end
local a = article.get_for(arguments[0]) 
%}

<div class="grey-row" id="headings">
  <div class="container row-2 font-light">
    <div class="clear row">
{% if arguments[1] == "edit" and headers["Cookie"] and session.is_logged_in(headers["Cookie"]) and method == "GET" then %}
{{[[
		<form action="" method="post">
		  <fieldset>
		    <legend>Edit</legend>
		    <div class="row clear">
		      <label class="block" for="title">Title</label>
		      <input type="text" name="title" cols="60" value="]].. a.title ..[[">
		    </div>
		    <div class="row clear">
		      <label class="block" for="image">Image</label>
		      <input type="text" name="image" cols="60" value="]].. a.image ..[[">
		    </div>
		    <div class="row clear">
		      <label class="block" for="abstract">Abstract</label>
   		     <textarea name="abstract" cols="60" rows="8">]].. a.abstract ..[[</textarea>
		    </div>
		    <div class="row clear">
     		 <label class="block" for="content">Content</label>
   		     <textarea name="content" cols="80" rows="20">]].. a.content ..[[</textarea>
   		     </div>
		      <input type="submit" value="Edit" class="button">
		  </fieldset>
		</form>
]]}}
{% else %}
{{[[
      <h2 class="h3 font-light">]].. a.title ..[[</h2>
      <p>]].. a.abstract ..[[</p>
      <img src="]].. a.image ..[[">
      <p>]].. a.content ..[[</p>
]]}}
{% end %}
    </div>
  </div>
</div>

{# footer #}

<script src="/file/js/default.js"></script>

</body>
</html>
