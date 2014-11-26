<!DOCTYPE html>
<html lang="en" class="no-js">
{# head #}
<body>
{% header = {title = "Main", abstract = "Some informative texts and tutorials"} %}
{# header #}

{%
if method == "POST" then
  local u = article()
  u.short_title = post["short_title"]
  u.title = post["title"]
  u.image = post["image"]
  article.add(u)
end
%}

<div class="grey-row" id="headings">
  <div class="container row-2 font-light">
    <div class="clear row">
{% if arguments[0] == "edit" and headers["Cookie"] and session.is_logged_in(headers["Cookie"]) and method == "GET" then %}
{{[[
    <form action="" method="post">
      <fieldset>
        <legend>Add</legend>
        <div class="row clear">
          <label class="block" for="short_title">Short Title</label>
          <input type="text" name="short_title" cols="60">
        </div>
        <div class="row clear">
          <label class="block" for="title">Title</label>
          <input type="text" name="title" cols="80">
        </div>
        <div class="row clear">
          <label class="block" for="image">Image</label>
          <input type="text" name="image" cols="60">
        </div>
        <input type="submit" value="Add" class="button">
      </fieldset>
    </form>
]]}}
{% else
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
end
%}
    </div>
  </div>
</div>

{# footer #}

<script src="/file/js/default.js"></script>

</body>
</html>
